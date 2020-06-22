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

    ///* number of unique vertices */
    //if (slices == 0 || stacks < 2)
    //{
    //    /* nothing to generate */
    //    *nVert = 0;
    //    return;
    //}
    int slices = 10;
	int stacks = 10;
    double radius = 100.0;
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

            //(*vertices)[idx] = x * radius;
            //(*vertices)[idx + 1] = y * radius;
            //(*vertices)[idx + 2] = z * radius;
            //(*normals)[idx] = x;
            //(*normals)[idx + 1] = y;
            //(*normals)[idx + 2] = z;
            LocalMesh->AppendVertex(FVertexInfo(
                FVector3d(x * radius, y * radius, z * radius),
                FVector3f(x, y, z),
                FVector3f(1.0, 1.0, 1.0)));
        }
    }

    ///* bottom */
    //(*vertices)[idx] = 0.f;
    //(*vertices)[idx + 1] = 0.f;
    //(*vertices)[idx + 2] = -radius;
    //(*normals)[idx] = 0.f;
    //(*normals)[idx + 1] = 0.f;
    //(*normals)[idx + 2] = -1.f;
    LocalMesh->AppendVertex(FVertexInfo(FVector3d(0.0, 0.0, -radius), FVector3f(0.0, 0.0, -1.0), FVector3f(1.0, 1.0, 1.0)));
    /* Done creating vertices, release sin and cos tables */
    free(sint1);
    free(cost1);
    free(sint2);
    free(cost2);

	//top triangles
	for(i = 0; i < slices; i+=3)
	{
		
	}

	// code to create index buffer for sphere, but it is parts which is not useful for us	
    int * stripIdx = (int *)malloc((slices + 1) * 2 * (stacks) * sizeof(int));

    /* top stack */
    for (j = 0, idx = 0; j < slices-1; j++, idx += 3)
    {
        stripIdx[idx] = 0;              /* 0 is top vertex, 1 is first for first stack */
        stripIdx[idx + 1] = (j + 1);
        stripIdx[idx + 2] = (j + 2);
    }
    stripIdx[idx] = 0;                    /* repeat first slice's idx for closing off shape */
    stripIdx[idx + 1] = ++j;
    stripIdx[idx + 2] = 1;
    idx += 3;

    int stackstart = 0;
    /* middle stacks: */
    /* Strip indices are relative to first index belonging to strip, NOT relative to first vertex/normal pair in array */
    for (i = 0; i < stacks - 2; i++, idx += 6)
    {
        stackstart = 1 + i * slices;                    /* triangle_strip indices start at 1 (0 is top vertex), and we advance one stack down as we go along */
        for (j = 0; j < slices-1; j++, idx += 6)
        {
        	//triangle 1
            stripIdx[idx] = stackstart + j; // next stack
            stripIdx[idx + 1] = stackstart + slices + j; //current stack
            stripIdx[idx + 2] = stackstart + j + 1; //current stack
			//triangle 2
            stripIdx[idx + 3] = stackstart + slices + j;
            stripIdx[idx + 4] = stackstart + slices + j + 1;
            stripIdx[idx + 5] = stackstart + slices + 1;
            //quad complete
        }
        ++j; //last vert in slice
        stripIdx[idx] = stackstart + j;        /* repeat first slice's idx for closing off shape */
        stripIdx[idx + 1] = stackstart + slices + j;
        stripIdx[idx + 2] = stackstart;
    	
        stripIdx[idx + 3] = stackstart + slices + j;
        stripIdx[idx + 4] = stackstart + slices;
        stripIdx[idx + 5] = stackstart;
        //last quad complete
    }

    ///* bottom stack */
    //offset = 1 + (stacks - 2) * slices;               /* triangle_strip indices start at 1 (0 is top vertex), and we advance one stack down as we go along */
    //for (j = 0; j < slices; j++, idx += 2)
    //{
    //    stripIdx[idx] = nVert - 1;              /* zero based index, last element in array (bottom vertex)... */
    //    stripIdx[idx + 1] = offset + j;
    //}
    //stripIdx[idx] = nVert - 1;                  /* repeat first slice's idx for closing off shape */
    //stripIdx[idx + 1] = offset;

    UE_LOG(LogTemp, Warning, TEXT("Max vertices: %d Number of verts in mesh: %d"), nVert, LocalMesh->VertexCount());

	for(int b = 0; b < idx; b+=3)
	{
        LocalMesh->AppendTriangle(FIndex3i(stripIdx[b], stripIdx[b + 1], stripIdx[b + 2]));
        //LocalMesh->AppendTriangle(FIndex3i(stripIdx[b+3], stripIdx[b + 1], stripIdx[b + 2]));
        //LocalMesh->SetVertexColor(b, FVector3f(1.0, 1.0, 1.0));
	}









	
 //  TEST STUFF - RECTANGLE AND ICOSPHERE WITH SUBDIVISION(NOT WORKING CORRECTLY)
 //   int index0 = LocalMesh->AppendVertex(FVector(0, -100, 0)); //lower left - 0
 //   int index1 = LocalMesh->AppendVertex(FVector(0, -100, 100)); // upper left - 1
 //   int index2 = LocalMesh->AppendVertex(FVector(0, 100, 0)); //lower right - 2 
 //   int index3 = LocalMesh->AppendVertex(FVector(0, 100, 100)); //upper right - 3

 //   int index4 = LocalMesh->AppendVertex(FVector(100, -100, 0)); //lower front left - 4
 //   int index5 = LocalMesh->AppendVertex(FVector(100, -100, 100)); //upper front left - 5

 //   int index6 = LocalMesh->AppendVertex(FVector(100, 100, 100)); //upper front right - 6
 //   int index7 = LocalMesh->AppendVertex(FVector(100, 100, 0)); //lower front right - 7

 //   LocalMesh->AppendTriangle(FIndex3i(index0, index2, index3));
 //   LocalMesh->AppendTriangle(FIndex3i(index3, index1, index0));

 //   LocalMesh->AppendTriangle(FIndex3i(index0, index1, index4));
 //   LocalMesh->AppendTriangle(FIndex3i(index4, index1, index5));

 //   LocalMesh->AppendTriangle(FIndex3i(index4, index5, index7));
 //   LocalMesh->AppendTriangle(FIndex3i(index7, index5, index6));

 //   LocalMesh->AppendTriangle(FIndex3i(index7, index6, index3));
 //   LocalMesh->AppendTriangle(FIndex3i(index3, index2, index7));

	//LocalMesh->AppendTriangle(FIndex3i(index1, index3, index5));
 //   LocalMesh->AppendTriangle(FIndex3i(index6, index5, index3));

 //   LocalMesh->AppendTriangle(FIndex3i(index2, index0, index4));
 //   LocalMesh->AppendTriangle(FIndex3i(index4, index7, index2));

	//
 //   LocalMesh->EnableVertexColors(FVector3f(1.0, 1.0, 1.0));

 //   LocalMesh->SetVertexColor(index0, FVector3f(0.f, 0.f, 1.f));
 //   LocalMesh->SetVertexColor(index1, FVector3f(1.f, 0.f, 0.f));
 //   LocalMesh->SetVertexColor(index2, FVector3f(1.f, 0.f, 0.f));
 //   LocalMesh->SetVertexColor(index3, FVector3f(0.f, 1.f, 0.f));
 //   LocalMesh->SetVertexColor(index4, FVector3f(0.5f, 1.0f, 0.5f));
 //   LocalMesh->SetVertexColor(index5, FVector3f(0.f, 1.f, 0.f));
 //   LocalMesh->SetVertexColor(index6, FVector3f(1.f, 1.f, 0.f));
 //   LocalMesh->SetVertexColor(index7, FVector3f(0.f, 1.f, 1.f));
 //
	//float t = (1.0 + sqrt(5.0)) / 2.0;
	//LocalMesh->AppendVertex(FVertexInfo(FVector3d(-1,  t,  0)));
 //   LocalMesh->AppendVertex(FVertexInfo(FVector3d(1, t, 0)));
 //   LocalMesh->AppendVertex(FVertexInfo(FVector3d(-1, -t, 0)));
 //   LocalMesh->AppendVertex(FVertexInfo(FVector3d(1, -t, 0)));

 //   LocalMesh->AppendVertex(FVertexInfo(FVector3d(0, -1, t)));
 //   LocalMesh->AppendVertex(FVertexInfo(FVector3d(0, 1, t)));
 //   LocalMesh->AppendVertex(FVertexInfo(FVector3d(0, -1, -t)));
 //   LocalMesh->AppendVertex(FVertexInfo(FVector3d(0, 1, -t)));

 //   LocalMesh->AppendVertex(FVertexInfo(FVector3d(t, 0, -1)));
 //   LocalMesh->AppendVertex(FVertexInfo(FVector3d(t, 0, 1)));
 //   LocalMesh->AppendVertex(FVertexInfo(FVector3d(-t, 0, -1)));
 //   LocalMesh->AppendVertex(FVertexInfo(FVector3d(-t, 0, 1)));

	////create triangles

 //   // 5 faces around point 0
 //   LocalMesh->AppendTriangle(FIndex3i(0, 11, 5));
 //   LocalMesh->AppendTriangle(FIndex3i(0, 5, 1));
 //   LocalMesh->AppendTriangle(FIndex3i(0, 1, 7));
 //   LocalMesh->AppendTriangle(FIndex3i(0, 7, 10));
 //   LocalMesh->AppendTriangle(FIndex3i(0, 10, 11));

 //   // 5 adjacent faces 
 //   LocalMesh->AppendTriangle(FIndex3i(1, 5, 9));
 //   LocalMesh->AppendTriangle(FIndex3i(5, 11, 4));
 //   LocalMesh->AppendTriangle(FIndex3i(11, 10, 2));
 //   LocalMesh->AppendTriangle(FIndex3i(10, 7, 6));
 //   LocalMesh->AppendTriangle(FIndex3i(7, 1, 8));

 //   // 5 faces around point 3
 //   LocalMesh->AppendTriangle(FIndex3i(3, 9, 4));
 //   LocalMesh->AppendTriangle(FIndex3i(3, 4, 2));
 //   LocalMesh->AppendTriangle(FIndex3i(3, 2, 6));
 //   LocalMesh->AppendTriangle(FIndex3i(3, 6, 8));
 //   LocalMesh->AppendTriangle(FIndex3i(3, 8, 9));

 //   // 5 adjacent faces 
 //   LocalMesh->AppendTriangle(FIndex3i(4, 9, 5));
 //   LocalMesh->AppendTriangle(FIndex3i(2, 4, 11));
 //   LocalMesh->AppendTriangle(FIndex3i(6, 2, 10));
 //   LocalMesh->AppendTriangle(FIndex3i(8, 6, 7));
 //   LocalMesh->AppendTriangle(FIndex3i(9, 8, 1));

 //   UE_LOG(LogTemp, Warning, TEXT("number vertices added: %d"), LocalMesh->VertexCount());
	//
	//Bake(EMeshInstance->GetMeshDescription(), false, FConversionToMeshDescriptionOptions());

 //   //EMeshInstance->SetSubdivisionCount(3);
 //   //InitializeMesh(EMeshInstance->GetMeshDescription());
	//
    NotifyMeshUpdated();
    //FastNotifyColorsUpdated();
	
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
