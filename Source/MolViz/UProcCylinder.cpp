// Fill out your copyright notice in the Description page of Project Settings.


#include "UProcCylinder.h"

UProcCylinder::UProcCylinder()
{
}

UProcCylinder::~UProcCylinder()
{
}

void UProcCylinder::GenerateCylinder(float radius, float height, int slices, int stacks)
{
    FDynamicMesh3* LocalMesh = GetMesh();
	
    int nVert = 0;

    int i, j;
    int idx = 0;    /* idx into vertex/normal buffer */

    /* Step in z as stacks are drawn. */
    float radf = (float)radius;
    float z;
    const float zStep = (float)height / ((stacks > 0) ? stacks : 1);

    /* Pre-computed circle */
    float* sint, * cost;

    /* number of unique vertices */
    if (slices == 0 || stacks < 1)
    {
        /* nothing to generate */
        nVert = 0;
        return;
    }
    nVert = slices * (stacks + 3) + 2;   /* need two extra stacks for closing off top and bottom with correct normals */

    if ((nVert) > 65535)
        /*
         * limit of glushort, thats 256*256 subdivisions, should be enough in practice. See note above
         */
        UE_LOG(LogTemp, Warning, TEXT("fghGenerateCylinder: too many slices or stacks requested, indices will wrap"));

    /* Pre-computed circle */
    fghCircleTable(&sint, &cost, -slices, false);

    /* Allocate vertex and normal buffers, bail out if memory allocation fails */
    //*vertices = malloc((*nVert) * 3 * sizeof(GLfloat));
    //*normals = malloc((*nVert) * 3 * sizeof(GLfloat));
    //if (!(*vertices) || !(*normals))
    //{
    //    free(*vertices);
    //    free(*normals);
    //    fgError("Failed to allocate memory in fghGenerateCylinder");
    //}

    z = 0;
    /* top on Z-axis */
    /*(*vertices)[0] = 0.f;
    (*vertices)[1] = 0.f;
    (*vertices)[2] = 0.f;*/
    LocalMesh->AppendVertex(FVertexInfo(FVector3d(0.f, 0.f, 0.f), FVector3f(0.f, 0.f, -1.f)));
    /*(*normals)[0] = 0.f;
    (*normals)[1] = 0.f;
    (*normals)[2] = -1.f;*/
    idx = 3;
    /* other on top (get normals right) */
    for (j = 0; j < slices; j++, idx += 3)
    {
        /*(*vertices)[idx] = cost[j] * radf;
        (*vertices)[idx + 1] = sint[j] * radf;
        (*vertices)[idx + 2] = z;*/
        LocalMesh->AppendVertex(FVertexInfo(FVector3d(cost[j] * radf, sint[j] * radf, z), FVector3f(0.f, 0.f, -1.f)));
        /*(*normals)[idx] = 0.f;
        (*normals)[idx + 1] = 0.f;
        (*normals)[idx + 2] = -1.f;*/
    }

    /* each stack */
    for (i = 0; i < stacks + 1; i++)
    {
        for (j = 0; j < slices; j++, idx += 3)
        {
            /*           (*vertices)[idx] = cost[j] * radf;
                       (*vertices)[idx + 1] = sint[j] * radf;
                       (*vertices)[idx + 2] = z;
                       (*normals)[idx] = cost[j];
                       (*normals)[idx + 1] = sint[j];
                       (*normals)[idx + 2] = 0.f;*/
            LocalMesh->AppendVertex(FVertexInfo(FVector3d(cost[j] * radf, sint[j] * radf, z), FVector3f(cost[j], sint[j], 0.f)));
        }

        z += zStep;
    }

    /* other on bottom (get normals right) */
    z -= zStep;
    for (j = 0; j < slices; j++, idx += 3)
    {
        //(*vertices)[idx] = cost[j] * radf;
        //(*vertices)[idx + 1] = sint[j] * radf;
        //(*vertices)[idx + 2] = z;
        //(*normals)[idx] = 0.f;
        //(*normals)[idx + 1] = 0.f;
        //(*normals)[idx + 2] = 1.f;
        LocalMesh->AppendVertex(FVertexInfo(FVector3d(cost[j] * radf, sint[j] * radf, z), FVector3f(0, 0, 1.f)));
    }

    /* bottom */
    //(*vertices)[idx] = 0.f;
    //(*vertices)[idx + 1] = 0.f;
    //(*vertices)[idx + 2] = height;
    //(*normals)[idx] = 0.f;
    //(*normals)[idx + 1] = 0.f;
    //(*normals)[idx + 2] = 1.f;
    LocalMesh->AppendVertex(FVertexInfo(FVector3d(0.f, 0.f, height), FVector3f(0.f, 0.f, 1.f)));
    /* Release sin and cos tables */
    free(sint);
    free(cost);

    // code to create index buffer for sphere, but it is parts which is not useful for us	
   /* top stack */
    for (j = 0, idx = 0; j < slices - 1; j++, idx += 3)
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
        for (j = 0; j < slices - 1; j++, idx += 6)
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
    for (j = 0; j < slices - 1; j++, idx += 3)
    {
        LocalMesh->AppendTriangle(nVert - 1, stackstart + j + 1, stackstart + j);
    }
    LocalMesh->AppendTriangle(nVert - 1, stackstart + ++j, stackstart);

    NotifyMeshUpdated();
}
