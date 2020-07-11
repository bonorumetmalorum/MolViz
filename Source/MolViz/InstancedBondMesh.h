// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FBondData.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "InstancedBondMesh.generated.h"

/**
 * 
 */
UCLASS()
class MOLVIZ_API UInstancedBondMesh : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:
	UInstancedBondMesh();
	void AddBond(FVector Position, FBondData BondData);
};
