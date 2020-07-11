// Fill out your copyright notice in the Description page of Project Settings.

#include "CPK.h"
#include "AProteinData.h"
#include "InstancedAtomMesh.h"
#include "InstancedBondMesh.h"

#include "UProcCylinder.h"
#include "UProcSphere.h"

void UCPK::AddAtom(const FAtomData& Atom)
{
	UProcSphere* Component = NewObject<UProcSphere>(this, UProcSphere::StaticClass());
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return;
	}
	Component->RegisterComponent();
	Component->SetWorldLocation(Atom.position);
	Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	Component->GenerateSphere(SphereStacks, SphereSlices, SphereRadius);
}

void UCPK::AddBond(const FVector& Position, const FVector& Direction)
{
	UProcCylinder* Component = NewObject<UProcCylinder>(this, UProcCylinder::StaticClass());
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return;
	}
	FMatrix Rotation = ComputeRotation(Direction);
	Component->SetWorldRotation(Rotation.Rotator());
	Component->RegisterComponent();
	Component->SetWorldLocation(Position);
	Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	Component->GenerateCylinder(CylinderRadius, Direction.Size() , CylinderSlices, CylinderStacks);
}

void UCPK::ConstructRepresentation(AProteinData* ProteinData)
{
	UInstancedBondMesh* BondComponent = NewObject<UInstancedBondMesh>(this, UInstancedBondMesh::StaticClass());
	UInstancedAtomMesh* AtomComponent = NewObject<UInstancedAtomMesh>(this, UInstancedAtomMesh::StaticClass());
	for (auto BondIter = ProteinData->Bonds.CreateConstIterator(); BondIter.GetIndex() < ProteinData->Bonds.Num(); ++BondIter)
	{
		FAtomData AtomA = ProteinData->Atoms[BondIter->AtomA];
		FAtomData AtomB = ProteinData->Atoms[BondIter->AtomB];
		//AddAtom(AtomA);
		//AddAtom(AtomB);
		//AddBond(AtomB.position, BondIter->Direction);
		BondComponent->AddBond((AtomA.position + AtomB.position) / 2, *BondIter);
	}
	for (auto AtomIter = ProteinData->Atoms.CreateConstIterator(); AtomIter.GetIndex() < ProteinData->Atoms.Num(); ++AtomIter)
	{
		AddAtom(*AtomIter);
		AtomComponent->AddAtom(&ProteinData->Atoms[AtomIter.GetIndex()]);
	}
	BondComponent->RegisterComponent();
	//BondComponent->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	AtomComponent->RegisterComponent();
	//AtomComponent->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
}

void UCPK::SetBondData(TArray<FBondData> *  InBondData)
{
	this->BondData = InBondData;
}

void UCPK::Config(const int InSphereStacks, const int InSphereSlices, const float InSphereRadius, const float InCylinderRadius, const int InCylinderSlices,
                  const int InCylinderStacks)
{
	this->SphereRadius = InSphereRadius;
	this->SphereSlices = InSphereSlices;
	this->SphereStacks = InSphereStacks;
	this->CylinderRadius = InCylinderRadius;
	this->CylinderSlices = InCylinderSlices;
	this->CylinderStacks = InCylinderStacks;
}


FMatrix UCPK::ComputeRotation(FVector A)
{
	return FRotationMatrix::MakeFromZ(A);
}
