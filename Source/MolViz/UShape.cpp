// Fill out your copyright notice in the Description page of Project Settings.


#include "UShape.h"
#include "MeshDescription.h"

UShape::UShape() : USimpleDynamicMeshComponent()
{
    bExplicitShowWireframe = false;
}

UShape::~UShape()
{
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
