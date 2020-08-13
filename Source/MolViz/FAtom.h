// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FAtom.generated.h"

/**
 * Represents 1 atom and all of its associated data
 */
USTRUCT(BlueprintType)
struct FAtomData
{
	GENERATED_BODY()

	FAtomData();
	/*
	 * constructor
	 * @param Snum serial number of the atom
	 * @param Alt alternative location index
	 * @param Name name of the atom
	 * @param Chain chain of the atom
	 * @param Resnum residude number of the atom
	 * @param Insertion_residue_code insertion residue code of the atom
	 * @param position 3d coordinates of the atom
	 * @param Occupancy occupancy of the atom
	 * @param TempFactor temp factor of the atom
	 * @param Element element type of the atom
	 */
	FAtomData(int32 Snum, uint8 Alt, FString Name, uint8 Chain, int32 Resnum, uint8 Insertion_residue_code, FVector position, float Occupancy, float TempFactor, FString Element);
	~FAtomData();
	/*
	 * Checks to see if the atom is a hydrogen atom
	 */
	bool IsHydrogen() const;
	
	int32 Snum;
	uint8 Alt;
	FString Name;
	uint8 Chain;
	int32 Resnum;
	int32 ResIndex;
	uint8 Insertion_residue_code;
	FVector position;
	float Occupancy;
	float TempFactor;
	FString Element;
	TArray<int> Neighbours;
};
