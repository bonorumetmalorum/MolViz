// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SimpleDynamicMeshComponent.h"

#include "DynamicMesh3.h"

#include "UShape.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MOLVIZ_API UShape : public USimpleDynamicMeshComponent
{
	GENERATED_BODY()
public:
	UShape();
	~UShape();
	void BeginPlay() override;
	virtual void ConstructShape();
	void fghCircleTable(float** sint, float** cost, const int n, const bool halfCircle);
};
