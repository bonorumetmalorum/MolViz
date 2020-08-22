// Fill out your copyright notice in the Description page of Project Settings.

#include "CPK.h"
#include "AProteinData.h"
#include "InstancedAtomMesh.h"
#include "InstancedBondMesh.h"

void UCPK::ConstructRepresentation(AProteinData* ProteinData)
{
	//create the instanced cylinder and sphere components
	BondMeshComponent = NewObject<UInstancedBondMesh>(this, UInstancedBondMesh::StaticClass());
	BondMeshComponent->SetWorldLocation(ProteinData->FindCOM());
	AtomMeshComponent = NewObject<UInstancedAtomMesh>(this, UInstancedAtomMesh::StaticClass());
	AtomMeshComponent->SetWorldLocation(ProteinData->FindCOM());
	//for all bonds render a bond
	for (auto BondIter = ProteinData->GetBonds().CreateConstIterator(); BondIter.GetIndex() < ProteinData->GetBonds().Num(); ++BondIter)
	{
		//get the two ends of the bond
		FAtomData AtomA = *ProteinData->GetAtom(BondIter->AtomA);
		FAtomData AtomB = *ProteinData->GetAtom(BondIter->AtomB);
		//add a new instanced bond
		BondMeshComponent->AddBond((AtomA.position + AtomB.position) / 2, *BondIter);
	}
	//for all atoms render a sphere
	for (auto AtomIter = ProteinData->GetAtoms().CreateConstIterator(); AtomIter.GetIndex() < ProteinData->GetAtoms().Num(); AtomIter++)
	{
		//get the color data for the element type
		FColorData * RowData = AtomColors->FindRow<FColorData>(FName(*(AtomIter->Element)), AtomIter->Name, true);
		if (RowData)
			//create the new instanced atom with the given color
			AtomMeshComponent->AddAtom(ProteinData->GetAtom(AtomIter.GetIndex()), RowData->color, 1.0);
		else
			//no color data was found render the default color
			AtomMeshComponent->AddAtom(ProteinData->GetAtom(AtomIter.GetIndex()), FLinearColor(102, 95, 37), 50.0);
	}
	//setup the components and attach them to the appropriate actor
	BondMeshComponent->RegisterComponent();
	BondMeshComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	AtomMeshComponent->RegisterComponent();
	AtomMeshComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	BondMeshComponent->SetMobility(EComponentMobility::Movable);
	AtomMeshComponent->SetMobility(EComponentMobility::Movable);
}

FMatrix UCPK::ComputeRotation(FVector A)
{
	return FRotationMatrix::MakeFromZ(A);
}
