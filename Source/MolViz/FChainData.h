// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FChainData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FChainData 
{
	GENERATED_BODY()
	
	FChainData();
	FChainData(int32 SerialNumber, FString Resname,	uint8 ChainID,int32 ResSeq,	uint8 CodeForInsertionsOfResidues, int StartAtomIndex, int EndAtomIndex);
	~FChainData();

	uint32 StartIndex;
	uint32 EndIndex;

	int32 SerialNumber;
	FString Resname;
	uint8 ChainID;
	int32 ResSeq;
	uint8 CodeForInsertionsOfResidues;
};
