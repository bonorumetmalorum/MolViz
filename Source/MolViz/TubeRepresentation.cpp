// Fill out your copyright notice in the Description page of Project Settings.


#include "TubeRepresentation.h"
#include "AProteinData.h"
#include "TubeComponent.h"

void UTubeRepresentation::ConstructRepresentation(AProteinData* ProteinData)
{
	for(auto BBIter = ProteinData->BackBone.CreateIterator(); BBIter;)
	{ //increment by residue
		if(BBIter.GetId().AsInteger() == 0)
		{//this is the first tube component, so we do not have access to a previous
			AddTubeSection(*BBIter, *(++BBIter), *(++BBIter));
		}
		else
		{//normal residue
			AddTubeSection(*BBIter, *(++BBIter), *(++BBIter));
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
}

void UTubeRepresentation::AddTubeSection(FAtomData* StartAtom, FAtomData* StartControlAtom, FAtomData* EndControlAtom, FAtomData* EndAtom)
{
	UTubeComponent* Component = NewObject<UTubeComponent>(this, UTubeComponent::StaticClass());
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return;
	}
	Component->SetBackbone(StartAtom, StartControlAtom, EndControlAtom, EndAtom); //refactor this into one method, which takes a boolean for start tube or not.
}