// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "InstancedAtomMesh.generated.h"
//forward declaration
struct FAtomData;
/**
 * a class to instantiate sphere at the positions of atoms
 */
UCLASS()
class MOLVIZ_API UInstancedAtomMesh : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()
public:
	UInstancedAtomMesh();
	/*
	 * adds a new instance of the mesh
	 * @param Atom the atom to add
	 * @param Color the color of the atom
	 * @param the radius of the atom
	 */
	void AddAtom(FAtomData* Atom, FLinearColor Color, float Radius);
};
