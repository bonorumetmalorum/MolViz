// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FBondData.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "InstancedBondMesh.generated.h"

/**
 * a class to keep track of all added bonds to the scene
 */
UCLASS()
class MOLVIZ_API UInstancedBondMesh : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:
	UInstancedBondMesh();
	/*
	 * adds a new bond to the scene
	 * @param Position the bonds position, where the center of the bond is at length / 2
	 * @param BondData the bond data
	 */
	void AddBond(FVector Position, FBondData BondData);
};
