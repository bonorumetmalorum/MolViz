// Fill out your copyright notice in the Description page of Project Settings.


#include "VDW.h"
#include "AProteinData.h"
#include "FVanDerWaalRadiiRowBase.h"
#include "InstancedAtomMesh.h"
#include "UObject/ConstructorHelpers.h"

UVDW::UVDW()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>RadiiData(TEXT("DataTable'/Game/VDWRadii.VDWRadii'"));
	VDWRadiiData = RadiiData.Object;
}

void UVDW::ConstructRepresentation(AProteinData * ProteinData)
{
	UInstancedAtomMesh* Component = NewObject<UInstancedAtomMesh>(this, UInstancedAtomMesh::StaticClass());
	for (auto iter = ProteinData->Residues.CreateConstIterator(); iter.GetIndex() < ProteinData->Residues.Num(); ++iter)
	{
		for (auto atomiter = iter->atoms.CreateConstIterator(); atomiter; atomiter++)
		{
			FColorData* RowData = AtomColors->FindRow<FColorData>(FName(*(ProteinData->Atoms[*atomiter].Element)), ProteinData->Atoms[*atomiter].Name, true);
			FVanDerWaalRadiiRowBase* Radii = VDWRadiiData->FindRow<FVanDerWaalRadiiRowBase>(FName(*(ProteinData->Atoms[*atomiter].Element)), ProteinData->Atoms[*atomiter].Name, true);

			if (RowData && Radii)
				Component->AddAtom(&ProteinData->Atoms[*atomiter], RowData->color, Radii->Radius);
			else
				Component->AddAtom(&ProteinData->Atoms[*atomiter], FLinearColor(102, 95, 37), 50.0);
		}
	}
	for(auto hetiter = ProteinData->HetResidues.CreateConstIterator(); hetiter; hetiter++)
	{
		for (auto hetatomiter = hetiter->atoms.CreateConstIterator(); hetatomiter; hetatomiter++)
		{
			FColorData* RowData = AtomColors->FindRow<FColorData>(FName(*(ProteinData->Atoms[*hetatomiter].Element)), ProteinData->Atoms[*hetatomiter].Name, true);
			FVanDerWaalRadiiRowBase* Radii = VDWRadiiData->FindRow<FVanDerWaalRadiiRowBase>(FName(*(ProteinData->Atoms[*hetatomiter].Element)), ProteinData->Atoms[*hetatomiter].Name, true);

			if (RowData && Radii)
				Component->AddAtom(&ProteinData->Atoms[*hetatomiter], RowData->color, Radii->Radius);
			else
				Component->AddAtom(&ProteinData->Atoms[*hetatomiter], FLinearColor(102, 95, 37), 50.0);
		}
	}
	Component->RegisterComponent();
	Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	Component->SetMobility(EComponentMobility::Movable);
}

void UVDW::SetSphereRes(int InStacks, int InSlices, float Radius)
{
	this->Stacks = InStacks;
	this->Slices = InSlices;
	this->SphereRadius = Radius;
}
