// Fill out your copyright notice in the Description page of Project Settings.


#include "TubeRepresentation.h"
#include "AProteinData.h"
#include "TubeComponent.h"

void UTubeRepresentation::ConstructRepresentation(AProteinData* ProteinData)
{
	if(ProteinData->BackBone.Num() == 0)
	{
		ProteinData->FindBackBone();
	}
	
	const int NumResidues = ProteinData->BackBone.Num() / 3;
	for(int Res = 0; Res < NumResidues; Res++)
	{ //increment by residue
		if(Res == 0)
		{//this is the first tube component, so we do not have access to a previous
			AddTubeSection(ProteinData->BackBone[Res*3], ProteinData->BackBone[(Res*3)+1], ProteinData->BackBone[(Res*3)+2]);
		}
		else
		{//normal residue
			AddTubeSection(
				ProteinData->BackBone[((Res-1)*3)+2], 
				ProteinData->BackBone[((Res) * 3)], 
				ProteinData->BackBone[(Res * 3) + 1], 
				ProteinData->BackBone[(Res * 3) + 2]
			);
		}
	}
}

void UTubeRepresentation::AddTubeSection(FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom)
{
	UTubeComponent* Component = NewObject<UTubeComponent>(this, UTubeComponent::StaticClass());
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return;
	}
	Component->SetStartingBackbone(StartAtom, ControlAtom, EndAtom);
	Component->RegisterComponent();
	//Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
}

void UTubeRepresentation::AddTubeSection(FAtomData* PreviousResLastAtom, FAtomData* PreviousResControlAtom, FAtomData* CurrentResControlAtom, FAtomData* CurrentResEndAtom)
{
	UTubeComponent* Component = NewObject<UTubeComponent>(this, UTubeComponent::StaticClass());
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return;
	}
	Component->SetBackbone(PreviousResLastAtom, PreviousResControlAtom, CurrentResControlAtom, CurrentResEndAtom); //refactor this into one method, which takes a boolean for start tube or not.
	Component->RegisterComponent();
	//Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
}