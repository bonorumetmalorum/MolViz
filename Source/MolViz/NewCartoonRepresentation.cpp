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
	//
	//
	if(ProteinData->BackBoneSegments.Num() == 0)
		ProteinData->FindBackBone();
	ChainState CurrentChainState = Invalid;
	for (int i = 0; i < ProteinData->BackBoneSegments.Num()-1; i++)
	{
		if (!ProteinData->BackBoneSegments[i].IsValid() || !ProteinData->BackBoneSegments[i + 1].IsValid())
			continue;
		
		CurrentChainState = UpdateChainState(ProteinData, i);
		UBackBoneComponent * SegmentComponent = nullptr;
		switch(ProteinData->BackBoneSegments[i].ResType)
		{
		case SSType::AHelix:
			if(i == ProteinData->Residues.Num()-1)
				SegmentComponent = AddAlphaHelixComponent(CurrentChainState, ProteinData->BackBoneSegments[i-1].CA, ProteinData->BackBoneSegments[i-1].C, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i].CA);
			else
				SegmentComponent = AddAlphaHelixComponent(CurrentChainState, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i].C, ProteinData->BackBoneSegments[i+1].CA, ProteinData->BackBoneSegments[i + 1].C);

			break;
		case SSType::BStrand:
			if(i == ProteinData->Residues.Num()-1)
				SegmentComponent = AddBetaSheetComponent(CurrentChainState, ProteinData->BackBoneSegments[i-1].CA, ProteinData->BackBoneSegments[i-1].C, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i].C);
			else
				SegmentComponent = AddBetaSheetComponent(CurrentChainState, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i].C, ProteinData->BackBoneSegments[i + 1].CA, ProteinData->BackBoneSegments[i + 1].C);

			break;
		case SSType::Coil:
			if(i == ProteinData->Residues.Num()-1)
				SegmentComponent = AddCoilComponent(CurrentChainState, ProteinData->BackBoneSegments[i-1].CA, ProteinData->BackBoneSegments[i-1].C, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i].C);
			else
				SegmentComponent = AddCoilComponent(CurrentChainState, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i].C, ProteinData->BackBoneSegments[i + 1].CA, ProteinData->BackBoneSegments[i + 1].C);
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("unknown type"));
		}
		if (!SegmentComponent || (ProteinData->BackBoneSegments[i].ResType == Coil)) continue;
		//TODO bug with this rotation, flipping to 180, need to average consecutive CAs
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

UBackBoneComponent* UNewCartoonRepresentation::AddAlphaHelixComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC)
{
	switch(CurrentChainState)
	{
	case Start:
		return AddBackBoneComponent<UHelixStartComponent>(NextCA, NextC, CurrentCA, CurrentC);
	case Middle:
		return AddBackBoneComponent<UHelixMiddleComponent>(CurrentCA, CurrentC, NextCA, NextC);
	case End:
		return AddBackBoneComponent<UHelixEndComponent>(CurrentCA, CurrentC, NextCA, NextC);
	case Invalid:
		UE_LOG(LogTemp, Warning, TEXT("invalid ss chain state"));
		return nullptr;
	}
	return nullptr;
}

UBackBoneComponent* UNewCartoonRepresentation::AddBetaSheetComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC)
{
	switch (CurrentChainState)
	{
	case Start:
		return AddBackBoneComponent<UBetaSheetStartComponent>(CurrentCA, CurrentC, NextCA, NextC);
	case Middle:
		return AddBackBoneComponent<UBetaSheetMiddleComponent>(CurrentCA, CurrentC, NextCA, NextC);
	case End:
		return AddBackBoneComponent<UBetaSheetEndComponent>(CurrentCA, CurrentC, NextCA, NextC);	
	case Invalid:
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
	if (CurrentResidue == 0) return Start;
	if (CurrentResidue >= ProteindData->Residues.Num() - 1) return End; //TODO bug with this index, residues not matching backbone segments???
	if (ProteindData->Residues[CurrentResidue - 1].SSResType != ProteindData->Residues[CurrentResidue].SSResType) return Start;
	if (ProteindData->Residues[CurrentResidue + 1].SSResType != ProteindData->Residues[CurrentResidue].SSResType) return End;
	return Middle;
}


