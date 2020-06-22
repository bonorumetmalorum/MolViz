// Fill out your copyright notice in the Description page of Project Settings.


#include "UShape.h"
#include "MeshDescription.h"

UShape::UShape() : USimpleDynamicMeshComponent()
{
    //ConstructShape();
    bExplicitShowWireframe = true;
    this->EMeshInstance = reinterpret_cast<UEditableMesh*>(UEditableMesh::StaticClass());
}

UShape::~UShape()
{
}

void UShape::BeginPlay()
{
    ConstructShape();
}

void UShape::ConstructShape()
{
    UE_LOG(LogTemp, Warning, TEXT("Shape Constructed"));
	FDynamicMesh3* LocalMesh = GetMesh();

    int i, j;
    int idx = 0;    /* idx into vertex/normal buffer */
    float x, y, z;

    /* Pre-computed circle */
    float* sint1, * cost1;
    float* sint2, * cost2;

    int slices = 10;
	int stacks = 10;
    double radius = 100.0;
    int nVert = slices * (stacks - 1) + 2; //slices then stacks
    if ((nVert) > 65535)
        UE_LOG(LogTemp, Warning, TEXT("fghGenerateSphere: too many slices or stacks requested, indices will wrap"));

    /* precompute values on unit circle */
    fghCircleTable(&sint1, &cost1, -slices, false);
    fghCircleTable(&sint2, &cost2, stacks, true);

    idx = 3;
    LocalMesh->AppendVertex(FVertexInfo(
        FVector3d(0.0,0.0,radius),
        FVector3f(0.0, 0.0, 1.0),
        FVector3f(1.0,1.0,1.0)));
    /* each stack */
    for (i = 1; i < stacks; i++)
    {
        for (j = 0; j < slices; j++, idx += 3)
        {
            x = cost1[j] * sint2[i];
            y = sint1[j] * sint2[i];
            z = cost2[i];
        	
            LocalMesh->AppendVertex(FVertexInfo(
                FVector3d(x * radius, y * radius, z * radius),
                FVector3f(x, y, z),
                FVector3f(1.0, 1.0, 1.0)));
        }
    }

    ///* bottom */
    LocalMesh->AppendVertex(FVertexInfo(FVector3d(0.0, 0.0, -radius), FVector3f(0.0, 0.0, -1.0), FVector3f(1.0, 1.0, 1.0)));
    /* Done creating vertices, release sin and cos tables */
    free(sint1);
    free(cost1);
    free(sint2);
    free(cost2);

	// code to create index buffer for sphere, but it is parts which is not useful for us	
    /* top stack */
    for (j = 0, idx = 0; j < slices-1; j++, idx += 3)
    {
        LocalMesh->AppendTriangle(0, (j + 1), (j + 2));
    }
    LocalMesh->AppendTriangle(0, ++j, 1);
    idx += 3;

    int stackstart = 0;
    /* middle stacks: */
    /* Strip indices are relative to first index belonging to strip, NOT relative to first vertex/normal pair in array */
    for (i = 0; i < stacks - 2; i++, idx += 6)
    {
        stackstart = 1 + (i * slices);                    /* triangle_strip indices start at 1 (0 is top vertex), and we advance one stack down as we go along */
        for (j = 0; j < slices-1; j++, idx += 6)
        {
        	//triangle 1
            LocalMesh->AppendTriangle(stackstart + j, stackstart + slices + j, stackstart + j + 1);
			//triangle 2
            LocalMesh->AppendTriangle(stackstart + slices + j, stackstart + slices + j + 1, stackstart + j + 1);
            //quad complete
        }
        LocalMesh->AppendTriangle(stackstart + j, stackstart + slices + j, stackstart);
        LocalMesh->AppendTriangle(stackstart + slices + j, stackstart + slices, stackstart);
        //last quad in ring complete
    }

    /* bottom stack */
    stackstart = 1 + (stacks - 2) * slices;               /* triangle_strip indices start at 1 (0 is top vertex), and we advance one stack down as we go along */
    for (j = 0; j < slices-1; j++, idx += 3)
    {
        LocalMesh->AppendTriangle(nVert - 1, stackstart + j + 1, stackstart + j);
    }
	LocalMesh->AppendTriangle(nVert - 1, stackstart + ++j, stackstart);
    UE_LOG(LogTemp, Warning, TEXT("Max vertices: %d Number of verts in mesh: %d"), nVert, LocalMesh->VertexCount());

    NotifyMeshUpdated();
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
