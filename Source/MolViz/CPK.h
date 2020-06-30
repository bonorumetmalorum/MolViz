// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Representation.h"
#include "CPK.generated.h"

/**
 * 
 */
UCLASS()
class MOLVIZ_API UCPK : public URepresentation
{
	GENERATED_BODY()

public:
	void AddAtom(const FAtomData& Atom);
	void AddBond(const FVector& Position, const FVector& Direction);
	void ConstructRepresentation(AProteinData * ProteinData/*, FColourScheme ColourScheme*/) override;
	void SetBondData(TArray<FBondData> * InBondData);
	void Config(int InSphereStacks, int InSphereSlices, float InSphereRadius, float InCylinderRadius, int InCylinderSlices, int InCylinderStacks);
	
private:
	static FMatrix ComputeRotation(FVector A);
	TArray<FBondData> * BondData;
	int SphereStacks;
	int SphereSlices;
	float SphereRadius;
	float CylinderRadius;
	int CylinderSlices;
	int CylinderStacks;
};
