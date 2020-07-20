// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FColorData.h"
#include "FVanDerWaalRadiiRowBase.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FVanDerWaalRadiiRowBase : public FTableRowBase
{
	GENERATED_BODY()
	
	FVanDerWaalRadiiRowBase();
	~FVanDerWaalRadiiRowBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AtomColorData)
	AtomType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AtomColorData)
	float Radius;
};
