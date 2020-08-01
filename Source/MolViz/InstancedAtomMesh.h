// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "InstancedAtomMesh.generated.h"

struct FAtomData;
/**
 * 
 */
UCLASS()
class MOLVIZ_API UInstancedAtomMesh : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()
public:
	UInstancedAtomMesh();
	void AddAtom(FAtomData* Atom, FLinearColor Color, float Radius);
	FBoxSphereBounds GetBoxSphereBounds();
};
