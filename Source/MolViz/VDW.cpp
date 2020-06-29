// Fill out your copyright notice in the Description page of Project Settings.


#include "VDW.h"
#include "AProteinData.h"
#include "UProcSphere.h"

UVDW::UVDW()
{
	
}

//TODO change to using FAtomData rather than X y z
void UVDW::AddAtom(float x, float y, float z)
{
	//const int NumComponents = GetComponents().Num();
	//UE_LOG(LogTemp, Warning, TEXT("Number of components on protein: %d"), NumComponents);
	//UProcSphere * Component = Cast<UProcSphere>(AddComponent(FName("ATOM"), false, FTransform(FVector(x, y, z)), UProcSphere::StaticClass()));

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
	for (auto iter = ProteinData->Residues.CreateConstIterator(); iter.GetIndex() < ProteinData->Residues.Num(); ++iter)
	{
		for (auto atomiter = iter->atoms.CreateConstIterator(); atomiter.GetIndex() < iter->atoms.Num(); ++atomiter)
		{
			AddAtom((*atomiter)->position.X, (*atomiter)->position.Y, (*atomiter)->position.Z);
		}
	}
}

void UVDW::SetSphereRes(int InStacks, int InSlices, float Radius)
{
	this->Stacks = InStacks;
	this->Slices = InSlices;
	this->SphereRadius = Radius;
}
