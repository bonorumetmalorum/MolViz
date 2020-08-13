// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSReader.h"

#include "FBackBoneSegmentData.generated.h"
//forward declaration
struct FAtomData;
/**
 *  represents the backbone atoms
 */
USTRUCT(BlueprintType)
struct FBackBoneSegmentData
{
	GENERATED_BODY()
	
	FBackBoneSegmentData();
	/*
	 * Constructor
	 * @param InN nitrogen atom
	 * @param InC carbon atom
	 * @param InCA alpha carbon atom
	 * @param InO oxygen atom
	 * @param InResType residue secondary structure type
	 */
	FBackBoneSegmentData(FAtomData* InN, FAtomData* InC, FAtomData *InCA, FAtomData* InO, SSType InResType);
	~FBackBoneSegmentData();

	FAtomData *N, *C, *CA, *O;
	SSType ResType;

	/*
	 * checks if this backbone segment is valid
	 * @return true if it is valid false otherwise
	 */
	bool IsValid();
};
