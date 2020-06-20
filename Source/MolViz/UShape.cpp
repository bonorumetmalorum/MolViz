// Fill out your copyright notice in the Description page of Project Settings.


#include "UShape.h"

UShape::UShape()
{
    ConstructShape();
}

UShape::~UShape()
{
}

void UShape::ConstructShape()
{
	FDynamicMesh3* LocalMesh = GetMesh();

    int i, j;
    int idx = 0;    /* idx into vertex/normal buffer */
    float x, y, z;

    /* Pre-computed circle */
    float* sint1, * cost1;
    float* sint2, * cost2;

    ///* number of unique vertices */
    //if (slices == 0 || stacks < 2)
    //{
    //    /* nothing to generate */
    //    *nVert = 0;
    //    return;
    //}
    int slices = 10;
	int stacks = 10;
    double radius = 5.0;
    int nVert = slices * (stacks - 1) + 2; //slices then stacks
    if ((nVert) > 65535)
        /*
         * limit of glushort, thats 256*256 subdivisions, should be enough in practice. See note above
         */
        UE_LOG(LogTemp, Warning, TEXT("fghGenerateSphere: too many slices or stacks requested, indices will wrap"));

    /* precompute values on unit circle */
    fghCircleTable(&sint1, &cost1, -slices, false);
    fghCircleTable(&sint2, &cost2, stacks, true);

    /* Allocate vertex and normal buffers, bail out if memory allocation fails */
    //*vertices = malloc((*nVert) * 3 * sizeof(GLfloat));
    //*normals = malloc((*nVert) * 3 * sizeof(GLfloat));
    //if (!(*vertices) || !(*normals))
    //{
    //    free(*vertices);
    //    free(*normals);
    //    fgError("Failed to allocate memory in fghGenerateSphere");
    //}

    ///* top */
    //(*vertices)[0] = 0.f;
    //(*vertices)[1] = 0.f;
    //(*vertices)[2] = radius;
    //(*normals)[0] = 0.f;
    //(*normals)[1] = 0.f;
    //(*normals)[2] = 1.f;
    idx = 3;
    LocalMesh->AppendVertex(FVertexInfo(FVector3d(0.0,0.0,radius), FVector3f(0.0, 0.0, 1.0)));
    /* each stack */
    for (i = 1; i < stacks; i++)
    {
        for (j = 0; j < slices; j++, idx += 3)
        {
            x = cost1[j] * sint2[i];
            y = sint1[j] * sint2[i];
            z = cost2[i];

            //(*vertices)[idx] = x * radius;
            //(*vertices)[idx + 1] = y * radius;
            //(*vertices)[idx + 2] = z * radius;
            //(*normals)[idx] = x;
            //(*normals)[idx + 1] = y;
            //(*normals)[idx + 2] = z;
            LocalMesh->AppendVertex(FVertexInfo(FVector3d(x * radius, y * radius, z * radius), FVector3f(x, y, z)));
        }
    }

    ///* bottom */
    //(*vertices)[idx] = 0.f;
    //(*vertices)[idx + 1] = 0.f;
    //(*vertices)[idx + 2] = -radius;
    //(*normals)[idx] = 0.f;
    //(*normals)[idx + 1] = 0.f;
    //(*normals)[idx + 2] = -1.f;
    LocalMesh->AppendVertex(FVertexInfo(FVector3d(0.0, 0.0, -radius), FVector3f(0.0, 0.0, -1.0)));

    /* Done creating vertices, release sin and cos tables */
    free(sint1);
    free(cost1);
    free(sint2);
    free(cost2);
}

void UShape::fghCircleTable(float** sint, float** cost, const int n, const bool halfCircle)
{
    int i;

    /* Table size, the sign of n flips the circle direction */
    const int size = abs(n);

    /* Determine the angle between samples */
    const float angle = (halfCircle ? 1 : 2) * (float)PI / (float)((n == 0) ? 1 : n);

    /* Allocate memory for n samples, plus duplicate of first entry at the end */
    *sint = (float *)malloc(sizeof(float) * (size + 1));
    *cost = (float *)malloc(sizeof(float) * (size + 1));

    /* Bail out if memory allocation fails, fgError never returns */
    if (!(*sint) || !(*cost))
    {
        free(*sint);
        free(*cost);
        UE_LOG(LogTemp, Warning, TEXT("Failed to allocate memory in fghCircleTable"));
    }

    /* Compute cos and sin around the circle */
    (*sint)[0] = 0.0;
    (*cost)[0] = 1.0;

    for (i = 1; i < size; i++)
    {
        (*sint)[i] = (float)sin(angle * i);
        (*cost)[i] = (float)cos(angle * i);
    }


    if (halfCircle)
    {
        (*sint)[size] = 0.0f;  /* sin PI */
        (*cost)[size] = -1.0f;  /* cos PI */
    }
    else
    {
        /* Last sample is duplicate of the first (sin or cos of 2 PI) */
        (*sint)[size] = (*sint)[0];
        (*cost)[size] = (*cost)[0];
    }
}
