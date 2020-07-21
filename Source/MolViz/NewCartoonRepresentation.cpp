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
	//iterate through the residues
	//find out what kind of ss rep is used in this residue
	ProteinData->FindBackBone();
	ChainState CurrentChainState = Invalid;
	for (int i = 0; i < ProteinData->Residues.Num(); i++)
	{
		if (!ProteinData->BackBoneSegments[i].IsValid() && !ProteinData->BackBoneSegments[i + 1].IsValid())
			continue;
		
		CurrentChainState = UpdateChainState(ProteinData, i);
		switch(ProteinData->Residues[i].SSResType)
		{
		case SSType::AHelix:
			if(i == ProteinData->Residues.Num()-1)
				AddAlphaHelixComponent(CurrentChainState, ProteinData->BackBoneSegments[i-1].CA, ProteinData->BackBoneSegments[i-1].C, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i].CA);
			else
				AddAlphaHelixComponent(CurrentChainState, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i].C, ProteinData->BackBoneSegments[i+1].CA, ProteinData->BackBoneSegments[i + 1].C);

			break;
		case SSType::BStrand:
			if(i == ProteinData->Residues.Num()-1)
				AddBetaSheetComponent(CurrentChainState, ProteinData->BackBoneSegments[i-1].CA, ProteinData->BackBoneSegments[i-1].C, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i].C);
			else
				AddBetaSheetComponent(CurrentChainState, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i].C, ProteinData->BackBoneSegments[i + 1].CA, ProteinData->BackBoneSegments[i + 1].C);

			break;
		case SSType::Coil:
			if(i == ProteinData->Residues.Num()-1)
				AddCoilComponent(CurrentChainState, ProteinData->BackBoneSegments[i-1].CA, ProteinData->BackBoneSegments[i-1].C, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i].C);
			else
				AddCoilComponent(CurrentChainState, ProteinData->BackBoneSegments[i].CA, ProteinData->BackBoneSegments[i].C, ProteinData->BackBoneSegments[i + 1].CA, ProteinData->BackBoneSegments[i + 1].C);
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("unknown type"));
		}
	}
}

void UNewCartoonRepresentation::AddAlphaHelixComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC)
{
	switch(CurrentChainState)
	{
	case Start:
		AddBackBoneComponent<UHelixStartComponent>(NextCA, NextC, CurrentCA, CurrentC);
		break;
	case Middle:
		AddBackBoneComponent<UHelixMiddleComponent>(CurrentCA, CurrentC, NextCA, NextC);
		break;
	case End:
		AddBackBoneComponent<UHelixEndComponent>(CurrentCA, CurrentC, NextCA, NextC);
		break;
	case Invalid:
		UE_LOG(LogTemp, Warning, TEXT("invalid ss chain state"));
		break;
	}
}

void UNewCartoonRepresentation::AddBetaSheetComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC)
{
	switch (CurrentChainState)
	{
	case Start:
		AddBackBoneComponent<UBetaSheetStartComponent>(CurrentCA, CurrentC, NextCA, NextC);
		break;
	case Middle:
		AddBackBoneComponent<UBetaSheetMiddleComponent>(CurrentCA, CurrentC, NextCA, NextC);

		break;
	case End:
		AddBackBoneComponent<UBetaSheetEndComponent>(CurrentCA, CurrentC, NextCA, NextC);

		break;
	case Invalid:
		UE_LOG(LogTemp, Warning, TEXT("invalid ss chain state"));
		break;
	}
}

void UNewCartoonRepresentation::AddCoilComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC)
{
	AddBackBoneComponent<UTubeComponent>(CurrentCA, CurrentC, NextCA, NextC);
}

UNewCartoonRepresentation::ChainState UNewCartoonRepresentation::UpdateChainState(AProteinData* ProteindData, int CurrentResidue)
{
	if (CurrentResidue == 0) return Start;
	if (CurrentResidue == ProteindData->Residues.Num() - 1) return End;
	if (ProteindData->Residues[CurrentResidue - 1].SSResType != ProteindData->Residues[CurrentResidue].SSResType) return Start;
	if (ProteindData->Residues[CurrentResidue + 1].SSResType != ProteindData->Residues[CurrentResidue].SSResType) return End;
	return Middle;
}


