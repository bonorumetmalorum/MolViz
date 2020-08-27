// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedAtomMesh.h"
#include "InstancedBondMesh.h"
#include "Representation.h"
#include "CPK.generated.h"

/**
 * CPK representation
 * adds and tracks all relevant meshes to render a CPK representation of the molecule
 */
UCLASS()
class MOLVIZ_API UCPK : public URepresentation
{
	GENERATED_BODY()

public:
	/*
	 * construct the representation
	 * @Param *ProteinData the protein data
	 */
	void ConstructRepresentation(AProteinData * ProteinData) override;
	
private:
	static FMatrix ComputeRotation(FVector A);
	TArray<FBondData> * BondData;
	UInstancedAtomMesh* AtomMeshComponent;
	UInstancedBondMesh* BondMeshComponent;
};
