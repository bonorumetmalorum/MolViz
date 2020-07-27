// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Representation.h"
#include "UObject/ConstructorHelpers.h"

#include "VDW.generated.h"

/**
 * 
 */
UCLASS()
class MOLVIZ_API UVDW : public URepresentation
{
	GENERATED_BODY()

public:
	UVDW();
	void ConstructRepresentation(AProteinData * ProteinData) override;
	void SetSphereRes(int Stacks, int Slices, float Radius);
	int Stacks = 5;
	int Slices = 5;
	float SphereRadius = 5.0f;
	UDataTable* VDWRadiiData;
};
