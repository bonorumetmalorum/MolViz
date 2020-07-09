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
	ChainState CurrentChainState = Invalid;
	for (int i = 0; i < ProteinData->Residues.Num(); i++)
	{
		CurrentChainState = UpdateChainState(ProteinData, i);
		switch(ProteinData->Residues[i].SSResType)
		{
		case SSType::AHelix:
			//check previous and next if possible
			//if previous is different ss type, this is
			break;
		case SSType::BStrand:
			break;
		case SSType::Coil:
			break;
		}
	}
}

void UNewCartoonRepresentation::AddAlphaHelixComponent(ChainState CurrentChainState, FAtomData* StartAtom,
	FAtomData* ControlAtom, FAtomData* EndAtom)
{
	switch(CurrentChainState)
	{
	case Start:
		AddBackBoneComponent<UHelixStartComponent>(StartAtom, ControlAtom, EndAtom);
		break;
	case Middle:
		AddBackBoneComponent<UHelixMiddleComponent>(StartAtom, ControlAtom, EndAtom);

		break;
	case End:
		AddBackBoneComponent<UHelixEndComponent>(StartAtom, ControlAtom, EndAtom);

		break;
	case Invalid:
		UE_LOG(LogTemp, Warning, TEXT("invalid ss chain state"));
		break;
	}
}

void UNewCartoonRepresentation::AddBetaSheetComponent(ChainState CurrentChainState, FAtomData* StartAtom,
	FAtomData* ControlAtom, FAtomData* EndAtom)
{
	switch (CurrentChainState)
	{
	case Start:
		AddBackBoneComponent<UBetaSheetStartComponent>(StartAtom, ControlAtom, EndAtom);
		break;
	case Middle:
		AddBackBoneComponent<UBetaSheetMiddleComponent>(StartAtom, ControlAtom, EndAtom);

		break;
	case End:
		AddBackBoneComponent<UBetaSheetEndComponent>(StartAtom, ControlAtom, EndAtom);

		break;
	case Invalid:
		UE_LOG(LogTemp, Warning, TEXT("invalid ss chain state"));
		break;
	}
}

void UNewCartoonRepresentation::AddCoilComponent(ChainState CurrentChainState, FAtomData* StartAtom,
	FAtomData* ControlAtom, FAtomData* EndAtom)
{
	AddBackBoneComponent<UTubeComponent>(StartAtom, ControlAtom, EndAtom);
}

ChainState UNewCartoonRepresentation::UpdateChainState(AProteinData* ProteindData, int CurrentResidue)
{
	if (CurrentResidue == 0) return Start;
	if (ProteindData->Residues[CurrentResidue - 1].SSResType != ProteindData->Residues[CurrentResidue].SSResType) return Start;
	if (ProteindData->Residues[CurrentResidue + 1].SSResType != ProteindData->Residues[CurrentResidue].SSResType) return End;
	if (CurrentResidue == ProteindData->Residues.Num() - 1) return End;
	return Middle;
}


