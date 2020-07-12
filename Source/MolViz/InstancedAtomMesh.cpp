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
	int InstanceID = AddInstance(FTransform(Atom->position));
	SetCustomPrimitiveDataVector4(InstanceID, FVector4(1.0, 1.0, 1.0, 1.0));
}
