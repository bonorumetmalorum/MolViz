// Fill out your copyright notice in the Description page of Project Settings.

#include "AProteinData.h"
#include "CPK.h"

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
	UProcCylinder* Component = NewObject<UProcCylinder>(this, UProcSphere::StaticClass());
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return;
	}
	Component->RegisterComponent();
	Component->SetWorldLocation(Position);
	Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	Component->GenerateCylinder(CylinderRadius, Direction.Size() , CylinderSlices, CylinderStacks);
}

void UCPK::ConstructRepresentation(AProteinData * ProteinData)
{
	for(auto BondIter = ProteinData->Bonds.CreateConstIterator(); BondIter.GetIndex() < ProteinData->Bonds.Num(); ++BondIter)
	{
		FAtomData AtomA = ProteinData->Atoms[BondIter->AtomA];
		FAtomData AtomB = ProteinData->Atoms[BondIter->AtomB];
		AddAtom(AtomA);
		AddAtom(AtomB);
		AddBond(AtomA.position, BondIter->Direction);
	}
}

void UCPK::SetBondData(TArray<FBondData> *  InBondData)
{
	this->BondData = InBondData;
}


FMatrix UCPK::ComputeRotation(FVector A)
{
	return FRotationMatrix::MakeFromZ(A);
}
