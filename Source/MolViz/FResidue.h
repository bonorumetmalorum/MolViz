// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAtom.h"
#include "FBondData.h"
#include "SSReader.h"


#include "FResidue.generated.h"

/**
 * keeps track of secondary structure info and all atoms within this residue
 */
USTRUCT(BlueprintType)
struct FResidue
{
	GENERATED_BODY()

	FResidue();
	/*
	 * constructor
	 * @param Resname residue name
	 * @param Resseq residue sequence number
	 */
	FResidue(const FString& Resname, int32 Resseq);
	~FResidue();

	TArray<int> atoms;
	TArray<int> bonds;
	FString Resname;
	int32 Resseq;
	SSType SSResType;

	bool operator==(int32 key);
};
