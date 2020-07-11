// Fill out your copyright notice in the Description page of Project Settings.


#include "InstancedAtomMesh.h"


#include "FAtom.h"
#include "UObject/ConstructorHelpers.h"

UInstancedAtomMesh::UInstancedAtomMesh()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Sphere.Sphere'"));
	UStaticMesh* Asset = Mesh.Object;
	UInstancedStaticMeshComponent::SetStaticMesh(Asset);
}

void UInstancedAtomMesh::AddAtom(FAtomData* Atom)
{
	AddInstance(FTransform(Atom->position));
}
