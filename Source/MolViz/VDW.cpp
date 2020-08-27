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
	AtomMeshComponent = NewObject<UInstancedAtomMesh>(this, UInstancedAtomMesh::StaticClass());
	for (auto iter = ProteinData->GetResidues().CreateConstIterator(); iter.GetIndex() < ProteinData->GetResidues().Num(); ++iter)
	{
		for (auto atomiter = iter->atoms.CreateConstIterator(); atomiter; atomiter++)
		{
			FColorData* RowData = AtomColors->FindRow<FColorData>(FName(*(ProteinData->GetAtoms()[*atomiter].Element)), ProteinData->GetAtoms()[*atomiter].Name, true);
			FVanDerWaalRadiiRowBase* Radii = VDWRadiiData->FindRow<FVanDerWaalRadiiRowBase>(FName(*(ProteinData->GetAtoms()[*atomiter].Element)), ProteinData->GetAtoms()[*atomiter].Name, true);

			if (RowData && Radii)
				AtomMeshComponent->AddAtom(&ProteinData->GetAtoms()[*atomiter], RowData->color, Radii->Radius);
			else
				AtomMeshComponent->AddAtom(&ProteinData->GetAtoms()[*atomiter], FLinearColor(102, 95, 37), 50.0);
		}
	}
	for(auto hetiter = ProteinData->GetHetResidues().CreateConstIterator(); hetiter; hetiter++)
	{
		for (auto hetatomiter = hetiter->atoms.CreateConstIterator(); hetatomiter; hetatomiter++)
		{
			FColorData* RowData = AtomColors->FindRow<FColorData>(FName(*(ProteinData->GetAtoms()[*hetatomiter].Element)), ProteinData->GetAtoms()[*hetatomiter].Name, true);
			FVanDerWaalRadiiRowBase* Radii = VDWRadiiData->FindRow<FVanDerWaalRadiiRowBase>(FName(*(ProteinData->GetAtoms()[*hetatomiter].Element)), ProteinData->GetAtoms()[*hetatomiter].Name, true);

			if (RowData && Radii)
				AtomMeshComponent->AddAtom(&ProteinData->GetAtoms()[*hetatomiter], RowData->color, Radii->Radius);
			else
				AtomMeshComponent->AddAtom(&ProteinData->GetAtoms()[*hetatomiter], FLinearColor(102, 95, 37), 50.0);
		}
	}
	AtomMeshComponent->RegisterComponent();
	AtomMeshComponent->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	AtomMeshComponent->SetMobility(EComponentMobility::Movable);
}
