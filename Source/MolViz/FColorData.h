// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FColorData.generated.h"

UENUM()
enum class AtomType : uint8
{
	H,
	O,
	N,
	C,
	S,
	P,
	Z,
	LPA,
	LPB
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FColorData : public FTableRowBase
{
	GENERATED_BODY()
	
	FColorData();
	~FColorData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AtomColorData)
	AtomType type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AtomColorData)
	FLinearColor color;
};
