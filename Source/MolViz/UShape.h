// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SimpleDynamicMeshComponent.h"

#include "DynamicMesh3.h"
#include "EditableMesh.h"
#include "UShape.generated.h"

/**
 * 
 */
UCLASS()
class MOLVIZ_API UShape : public USimpleDynamicMeshComponent
{
	GENERATED_BODY()
public:
	UShape();
	~UShape();
	void fghCircleTable(float** sint, float** cost, const int n, const bool halfCircle);
};
