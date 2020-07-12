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

void UInstancedAtomMesh::AddAtom(FAtomData* Atom, FLinearColor Color)
{
	int InstanceID = AddInstance(FTransform(Atom->position));
	//SetCustomPrimitiveDataVector4(InstanceID, FVector4(Color));
	TArray<float> rgba = {Color.R, Color.G, Color.B, Color.A};
	SetCustomData(InstanceID, rgba, true);
}
