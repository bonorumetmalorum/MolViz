// Fill out your copyright notice in the Description page of Project Settings.


#include "InstancedAtomMesh.h"


#include "FAtom.h"
#include "UObject/ConstructorHelpers.h"

UInstancedAtomMesh::UInstancedAtomMesh()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Sphere.Sphere'"));
	UStaticMesh* Asset = Mesh.Object;
	UInstancedStaticMeshComponent::SetStaticMesh(Asset);
	NumCustomDataFloats = 4;
}

void UInstancedAtomMesh::AddAtom(FAtomData* Atom, FLinearColor Color, float Radius)
{
	int InstanceID = AddInstanceWorldSpace(FTransform(FRotator::ZeroRotator, Atom->position, FVector(Radius)));
	TArray<float> rgba = {Color.R, Color.G, Color.B, Color.A};
	SetCustomData(InstanceID, rgba, true);
}
