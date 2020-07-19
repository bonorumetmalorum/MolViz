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
		CurrentChainState = UpdateChainState(ProteinData, i);
		switch(ProteinData->Residues[i].SSResType)
		{
		case SSType::AHelix:
			if(i == ProteinData->Residues.Num()-1)
				AddAlphaHelixComponent(CurrentChainState, ProteinData->BackBone[(i-1) * 3], ProteinData->BackBone[(i-1) * 3 + 2], ProteinData->BackBone[(i) * 3], ProteinData->BackBone[(i) * 3 + 2]);
			else
				AddAlphaHelixComponent(CurrentChainState, ProteinData->BackBone[i * 3], ProteinData->BackBone[i * 3 + 2], ProteinData->BackBone[(i + 1) * 3], ProteinData->BackBone[(i + 1) * 3 + 2]);

			break;
		case SSType::BStrand:
			if(i == ProteinData->Residues.Num()-1)
				AddBetaSheetComponent(CurrentChainState, ProteinData->BackBone[(i-1) * 3], ProteinData->BackBone[(i-1) * 3 + 2], ProteinData->BackBone[(i) * 3], ProteinData->BackBone[(i) * 3 + 2]);
			else
				AddBetaSheetComponent(CurrentChainState, ProteinData->BackBone[i * 3], ProteinData->BackBone[i * 3 + 2], ProteinData->BackBone[(i + 1) * 3], ProteinData->BackBone[(i + 1) * 3 + 2]);

			break;
		case SSType::Coil:
			if(i == ProteinData->Residues.Num()-1)
				AddCoilComponent(CurrentChainState, ProteinData->BackBone[(i -1) * 3], ProteinData->BackBone[(i-1) * 3 + 2], ProteinData->BackBone[(i) * 3], ProteinData->BackBone[(i) * 3 + 2]);
			else
				AddCoilComponent(CurrentChainState, ProteinData->BackBone[i * 3], ProteinData->BackBone[i * 3 + 2], ProteinData->BackBone[(i + 1) * 3], ProteinData->BackBone[(i + 1) * 3 + 2]);
			break;
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


