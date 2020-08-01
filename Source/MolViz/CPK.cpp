// Fill out your copyright notice in the Description page of Project Settings.

#include "CPK.h"
#include "AProteinData.h"
#include "InstancedAtomMesh.h"
#include "InstancedBondMesh.h"

void UCPK::ConstructRepresentation(AProteinData* ProteinData)
{
	UInstancedBondMesh* BondComponent = NewObject<UInstancedBondMesh>(this, UInstancedBondMesh::StaticClass());
	BondComponent->SetWorldLocation(ProteinData->FindCOM());
	UInstancedAtomMesh* AtomComponent = NewObject<UInstancedAtomMesh>(this, UInstancedAtomMesh::StaticClass());
	AtomComponent->SetWorldLocation(ProteinData->FindCOM());

	for (auto BondIter = ProteinData->Bonds.CreateConstIterator(); BondIter.GetIndex() < ProteinData->Bonds.Num(); ++BondIter)
	{
		FAtomData AtomA = ProteinData->Atoms[BondIter->AtomA];
		FAtomData AtomB = ProteinData->Atoms[BondIter->AtomB];
		BondComponent->AddBond((AtomA.position + AtomB.position) / 2, *BondIter);
	}
	for (auto AtomIter = ProteinData->Atoms.CreateConstIterator(); AtomIter.GetIndex() < ProteinData->Atoms.Num(); AtomIter++)
	{
		FColorData * RowData = AtomColors->FindRow<FColorData>(FName(*(AtomIter->Element)), AtomIter->Name, true);
		if (RowData)
			AtomComponent->AddAtom(&ProteinData->Atoms[AtomIter.GetIndex()], RowData->color, 1.0);
		else
			AtomComponent->AddAtom(&ProteinData->Atoms[AtomIter.GetIndex()], FLinearColor(102, 95, 37), 50.0);
	}
	BondComponent->RegisterComponent();
	BondComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	AtomComponent->RegisterComponent();
	AtomComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	BondComponent->SetMobility(EComponentMobility::Movable);
	AtomComponent->SetMobility(EComponentMobility::Movable);
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
