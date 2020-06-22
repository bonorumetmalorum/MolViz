// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UShape.h"
#include "UProcCylinder.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MOLVIZ_API UProcCylinder : public UShape
{
	GENERATED_BODY()
public:
	UProcCylinder();
	~UProcCylinder();
	UFUNCTION(BlueprintCallable)
	void GenerateCylinder(float radius, float height, int slices, int stacks);
};
