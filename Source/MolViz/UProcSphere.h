// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UShape.h"
#include "UProcSphere.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MOLVIZ_API UProcSphere : public UShape
{
	GENERATED_BODY()
public:
	UProcSphere();
	~UProcSphere();
	UFUNCTION(BlueprintCallable)
	void GenerateSphere(int stacks, int slices, float radius);
};
