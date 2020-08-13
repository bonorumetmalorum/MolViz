// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAtom.h"

#include "FBondData.generated.h"
/**
 * represents a single bond between two atoms
 */
USTRUCT(BlueprintType)
struct FBondData 
{
	GENERATED_BODY()
	
	FBondData();
	/*
	 * Constructor
	 * @param AtomA the first atom
	 * @param AtomB the second atom
	 * @param Direction the direction from the first to the second atom
	 */
	FBondData(int AtomA, int AtomB, FVector Direction);
	~FBondData();

	int AtomA;
	int AtomB;
	FVector Direction;
};
