// Fill out your copyright notice in the Description page of Project Settings.


#include "NewCartoonRepresentation.h"
#include "AProteinData.h"
#include "HelixStartComponent.h"
#include "HelixMiddleComponent.h"
#include "HelixEndComponent.h"
#include "BetaSheetStartComponent.h"
#include "BetaSheetMiddleComponent.h"
#include "BetaSheetEndComponent.h"
#include "TubeComponent.h"


void UNewCartoonRepresentation::ConstructRepresentation(AProteinData* ProteinData)
{
	FMatrix PreviousRot;
	//iterate through the residues
	//find out what kind of ss rep is used in this residue
	if(ProteinData->GetBackBoneSegments().Num() == 0)
		ProteinData->FindBackBone();
	ChainState CurrentChainState = ChainInvalid;
	for(auto ChainIter = ProteinData->GetChains().CreateConstIterator(); ChainIter; ChainIter++)
	{//for all chains
		for (uint32 i = ChainIter->StartBackBoneIndex; i < ChainIter->EndBackBoneIndex - 1; i++)
		{//for all backbone segments in this chain
			if (!ProteinData->GetBackBoneSegment(i)->IsValid() || !ProteinData->GetBackBoneSegment(i + 1)->IsValid())
				continue; //skip if current or next is not valid backbone segment
			//update the current chain state, used to keep track of start, middle and end of a SS type
			CurrentChainState = UpdateChainState(ProteinData, i);
			UBackBoneComponent* SegmentComponent = nullptr;
			//switch on the ss type of the current segment
			switch (ProteinData->GetBackBoneSegment(i)->ResType)
			{
			case SSType::AHelix: //add a helix component
				SegmentComponent = AddAlphaHelixComponent(CurrentChainState, ProteinData->GetBackBoneSegment(i)->CA, ProteinData->GetBackBoneSegment(i)->C, ProteinData->GetBackBoneSegment(i + 1)->CA, ProteinData->GetBackBoneSegment(i + 1)->C);
				break;
			case SSType::BStrand: //add a beta strand / beta sheet component
				SegmentComponent = AddBetaSheetComponent(CurrentChainState, ProteinData->GetBackBoneSegment(i)->CA, ProteinData->GetBackBoneSegment(i)->C, ProteinData->GetBackBoneSegment(i + 1)->CA, ProteinData->GetBackBoneSegment(i + 1)->C);
				break;
			case SSType::Coil: //add a coil component
				SegmentComponent = AddCoilComponent(CurrentChainState, ProteinData->GetBackBoneSegment(i)->CA, ProteinData->GetBackBoneSegment(i)->C, ProteinData->GetBackBoneSegment(i + 1)->CA, ProteinData->GetBackBoneSegment(i + 1)->C);
				break;
			default: //add a coil component if no ss type matched
				SegmentComponent = AddCoilComponent(CurrentChainState, ProteinData->GetBackBoneSegment(i)->CA, ProteinData->GetBackBoneSegment(i)->C, ProteinData->GetBackBoneSegment(i + 1)->CA, ProteinData->GetBackBoneSegment(i + 1)->C); UE_LOG(LogTemp, Warning, TEXT("unknown type"));
				break;
			}
	}
	
		//TODO incomplete / incorrect code to set rotations
		//if it is the begining, we dont have a previous segment to do
		//if it is at the end we dont have a next segment to do
		//if(i == 0)
		//{
		//	FMatrix EndRotation = SegmentComponent->MakeRotation(ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i+1].CA, ProteinData->BackBoneSegments[i].O); //current carbon, next carbon and current oxygen
		//	SegmentComponent->SetStartRoll(EndRotation.Rotator().Roll);
		//	SegmentComponent->SetEndRoll(EndRotation.Rotator().Roll);
		//	PreviousRot = EndRotation;
		//}
		//else if(i == ProteinData->BackBoneSegments.Num()-1)
		//{
		//	FMatrix StartRotation = SegmentComponent->MakeRotation(ProteinData->BackBoneSegments[i-1].CA, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i-1].O); //current carbon, next carbon and current oxygen
		//	SegmentComponent->SetStartRoll(PreviousRot.Rotator().Roll);
		//	SegmentComponent->SetEndRoll(PreviousRot.Rotator().Roll);
		//}
		//else
		//{
		//	//FMatrix StartRotation = SegmentComponent->MakeRotation(ProteinData->BackBoneSegments[i - 1].CA, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i - 1].O); //current carbon, next carbon and current oxygen
		//	FMatrix EndRotation = SegmentComponent->MakeRotation(ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i + 1].CA, ProteinData->BackBoneSegments[i].O); //current carbon, next carbon and current oxygen
		//	if(FVector::DotProduct(PreviousRot.GetUnitAxis(EAxis::Y), EndRotation.GetUnitAxis(EAxis::Y)) <= 0.0f)
		//	{//the rotation is greater than 90 degrees
		//		FRotator NewEnd = EndRotation.Rotator();
		//		NewEnd.Add(0,0,180);
		//		SegmentComponent->SetStartRoll(PreviousRot.Rotator().Roll);
		//		SegmentComponent->SetEndRoll(EndRotation.Rotator().Roll);
		//		PreviousRot = FRotationMatrix(NewEnd);
		//	}
		//	else
		//	{
		//		SegmentComponent->SetStartRoll(PreviousRot.Rotator().Roll);
		//		SegmentComponent->SetEndRoll(EndRotation.Rotator().Roll);
		//		PreviousRot = EndRotation;
		//	}			
		//}
	}
}

FBoxSphereBounds UNewCartoonRepresentation::CalcBounds(const FTransform& LocalToWorld) const
{
	return FBoxSphereBounds();
}

UBackBoneComponent* UNewCartoonRepresentation::AddAlphaHelixComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC)
{
	switch(CurrentChainState)
	{
	case ChainStart:
		return AddBackBoneComponent<UHelixStartComponent>(NextCA, NextC, CurrentCA, CurrentC);
	case ChainMiddle:
		return AddBackBoneComponent<UHelixMiddleComponent>(CurrentCA, CurrentC, NextCA, NextC);
	case ChainEnd:
		return AddBackBoneComponent<UHelixEndComponent>(CurrentCA, CurrentC, NextCA, NextC);
	case ChainInvalid:
		UE_LOG(LogTemp, Warning, TEXT("invalid ss chain state"));
		return nullptr;
	}
	return nullptr;
}

UBackBoneComponent* UNewCartoonRepresentation::AddBetaSheetComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC)
{
	switch (CurrentChainState)
	{
	case ChainStart:
		return AddBackBoneComponent<UBetaSheetStartComponent>(CurrentCA, CurrentC, NextCA, NextC);
	case ChainMiddle:
		return AddBackBoneComponent<UBetaSheetMiddleComponent>(CurrentCA, CurrentC, NextCA, NextC);
	case ChainEnd:
		return AddBackBoneComponent<UBetaSheetEndComponent>(CurrentCA, CurrentC, NextCA, NextC);	
	case ChainInvalid:
		UE_LOG(LogTemp, Warning, TEXT("invalid ss chain state"));
		return nullptr;
	}
	return nullptr;
}

UBackBoneComponent* UNewCartoonRepresentation::AddCoilComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC)
{
	return AddBackBoneComponent<UTubeComponent>(CurrentCA, CurrentC, NextCA, NextC);
}

UNewCartoonRepresentation::ChainState UNewCartoonRepresentation::UpdateChainState(AProteinData* ProteindData, int CurrentResidue)
{
	if (CurrentResidue == 0) return ChainStart;
	if (CurrentResidue >= ProteindData->GetResidues().Num() - 1) return ChainEnd;
	if (ProteindData->GetResidues()[CurrentResidue - 1].SSResType != ProteindData->GetResidues()[CurrentResidue].SSResType) return ChainStart;
	if (ProteindData->GetResidues()[CurrentResidue + 1].SSResType != ProteindData->GetResidues()[CurrentResidue].SSResType) return ChainEnd;
	return ChainMiddle;
}


