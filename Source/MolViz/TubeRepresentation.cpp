// Fill out your copyright notice in the Description page of Project Settings.


#include "TubeRepresentation.h"
#include "AProteinData.h"
#include "BackBoneComponent.h"
#include "TubeComponent.h"

void UTubeRepresentation::ConstructRepresentation(AProteinData* ProteinData)
{
	if(ProteinData->GetBackBoneSegments().Num() == 0)
	{
		ProteinData->FindBackBone();
	}
	this->SetWorldLocation(ProteinData->FindCOM());
	const int NumResidues = ProteinData->GetBackBoneSegments().Num();
	for(auto ChainIter = ProteinData->GetChains().CreateConstIterator(); ChainIter; ChainIter++)
	{//for all chains
		for(uint32 BackBoneSeg = ChainIter->StartBackBoneIndex; BackBoneSeg <= ChainIter->EndBackBoneIndex-2; BackBoneSeg++)
		{//for all backbone segments in this chain
			if (ProteinData->GetBackBoneSegments()[BackBoneSeg].IsValid() && ProteinData->GetBackBoneSegments()[BackBoneSeg + 1].IsValid()) //if valid backbone segment
				//insert new tube
				AddTubeSection(ProteinData->GetBackBoneSegments()[BackBoneSeg].CA, ProteinData->GetBackBoneSegments()[BackBoneSeg].C, ProteinData->GetBackBoneSegments()[BackBoneSeg + 1].CA, ProteinData->GetBackBoneSegments()[BackBoneSeg + 1].C);
		}
	}
}
//we are passing in CA, N, C where actually for tube we need CA, C, CA, C where the first CA, C pair are from the same amino acid / residue, the same for the second.
void UTubeRepresentation::AddTubeSection(FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom)
{
	UTubeComponent* Component = NewObject<UTubeComponent>(this, UTubeComponent::StaticClass());
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return;
	}
	Component->SetStartingBackbone(StartAtom, ControlAtom, EndAtom);
	Component->SetMobility(EComponentMobility::Movable);
	Component->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	Component->RegisterComponent();
}

void UTubeRepresentation::AddTubeSection(FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC)
{
	//CA C CA C
	UTubeComponent* Component = NewObject<UTubeComponent>(this, UTubeComponent::StaticClass());
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return;
	}
	Component->SetBackbone(CurrentCA, CurrentC, NextCA, NextC); //refactor this into one method, which takes a boolean for start tube or not.
	Component->SetMobility(EComponentMobility::Movable);
	Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	Component->RegisterComponent();
}