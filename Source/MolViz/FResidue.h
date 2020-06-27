// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAtom.h"
#include "FResidue.generated.h"

/**
 * keeps track of secondary structure info and all atoms within this residue
 */
USTRUCT(BlueprintType)
struct FResidue
{
	GENERATED_BODY()

	FResidue();
	FResidue(const FString& Resname, int32 Resseq);
	~FResidue();

	TArray<FAtomData *> atoms;
	FString Resname;
	int32 Resseq;
};
