// Fill out your copyright notice in the Description page of Project Settings.


#include "InstancedBondMesh.h"


#include "FBondData.h"
#include "UObject/ConstructorHelpers.h"

UInstancedBondMesh::UInstancedBondMesh()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Cylinder.Cylinder'"));
	UStaticMesh* Asset = Mesh.Object;
	UInstancedStaticMeshComponent::SetStaticMesh(Asset);
}

void UInstancedBondMesh::AddBond(FVector Position, FBondData BondData)
{
	FMatrix Rotation = FRotationMatrix::MakeFromY(BondData.Direction);
	float mag = BondData.Direction.Size();
	AddInstance(FTransform(Rotation.Rotator(), Position, FVector(0.5, mag, 0.5)));
}
