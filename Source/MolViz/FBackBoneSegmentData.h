// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FBackBoneSegmentData.generated.h"

struct FAtomData;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FBackBoneSegmentData
{
	GENERATED_BODY()
	
	FBackBoneSegmentData();
	FBackBoneSegmentData(FAtomData* InN, FAtomData* InC, FAtomData *InCA, FAtomData* InO);
	~FBackBoneSegmentData();

	FAtomData *N, *C, *CA, *O;

	bool IsValid();
};
