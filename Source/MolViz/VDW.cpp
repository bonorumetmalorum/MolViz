// Fill out your copyright notice in the Description page of Project Settings.


#include "VDW.h"
#include "AProteinData.h"
#include "FVanDerWaalRadiiRowBase.h"
#include "InstancedAtomMesh.h"
#include "UProcSphere.h"
#include "UObject/ConstructorHelpers.h"

UVDW::UVDW()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>RadiiData(TEXT("DataTable'/Game/VDWRadii.VDWRadii'"));
	VDWRadiiData = RadiiData.Object;
}

//TODO change to using FAtomData rather than X y z
void UVDW::AddAtom(float x, float y, float z)
{
	UProcSphere* Component = NewObject<UProcSphere>(this, UProcSphere::StaticClass());
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return;
	}
	Component->RegisterComponent();
	Component->SetWorldLocation(FVector(x, y, z));
	Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	Component->GenerateSphere(Stacks, Slices, SphereRadius);
}

void UVDW::ConstructRepresentation(AProteinData * ProteinData)
{
	UInstancedAtomMesh* Component = NewObject<UInstancedAtomMesh>(this, UInstancedAtomMesh::StaticClass());
	for (auto iter = ProteinData->Residues.CreateConstIterator(); iter.GetIndex() < ProteinData->Residues.Num(); ++iter)
	{
		for (auto atomiter = iter->atoms.CreateConstIterator(); atomiter.GetIndex() < iter->atoms.Num(); ++atomiter)
		{
			FColorData* RowData = AtomColors->FindRow<FColorData>(FName(*(ProteinData->Atoms[*atomiter].Element)), ProteinData->Atoms[*atomiter].Name, true);
			FVanDerWaalRadiiRowBase* Radii = VDWRadiiData->FindRow<FVanDerWaalRadiiRowBase>(FName(*(ProteinData->Atoms[*atomiter].Element)), ProteinData->Atoms[*atomiter].Name, true);

			if (RowData && Radii)
				Component->AddAtom(&ProteinData->Atoms[*atomiter], RowData->color, Radii->Radius);
			else
				Component->AddAtom(&ProteinData->Atoms[*atomiter], FLinearColor(102, 95, 37), 1.0);
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
