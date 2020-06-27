// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAtom.h"

#include "FBondData.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FBondData 
{
	GENERATED_BODY()
	
	FBondData();
	~FBondData();

	FAtomData* AtomA;
	FAtomData* AtomB;
};
