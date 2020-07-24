// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FResidue.h"

#include "FChainData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FChainData 
{
	GENERATED_BODY()
	
	FChainData();
	FChainData(int32 SerialNumber, FString Resname,	uint8 ChainID,int32 ResSeq,	uint8 CodeForInsertionsOfResidues, int StartResInex, int EndResIndex);
	~FChainData();

	uint32 StartIndex;
	uint32 EndIndex;

	int32 SerialNumber;
	FString Resname;
	uint8 ChainID;
	int32 ResSeq;
	uint8 CodeForInsertionsOfResidues;
	TArray<TPair<uint32, uint32>> ResidueOffsets;
	bool operator==(uint8 Index);
};

//TODO maybe add an array of residues here, move it from the protein data class.
//we need to do this because residue numbers are repeated for each chain.
//also residue numbers dont necessarily start from 1... what a pain.
//this will just store the residue start and end indices. easier this way. still have data locality for all arrays.