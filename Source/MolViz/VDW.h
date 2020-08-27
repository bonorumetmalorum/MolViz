// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedAtomMesh.h"
#include "Representation.h"
#include "UObject/ConstructorHelpers.h"

#include "VDW.generated.h"

/**
 * a class for the VDW representation
 */
UCLASS()
class MOLVIZ_API UVDW : public URepresentation
{
	GENERATED_BODY()

public:
	UVDW();
	/**
	 * create a VDW representation of the protein data
	 * @param ProteinData the protein data to represent in VDW
	 */
	void ConstructRepresentation(AProteinData * ProteinData) override;
	float SphereRadius = 5.0f;
	UDataTable* VDWRadiiData;
	UInstancedAtomMesh* AtomMeshComponent;
};
