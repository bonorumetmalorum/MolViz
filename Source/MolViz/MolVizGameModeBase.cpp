// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "MolVizGameModeBase.h"

#include "MousePlayerController.h"
#include "ProteinRepresentation.h"

AMolVizGameModeBase::AMolVizGameModeBase() : Super()
{
	UE_LOG(LogTemp, Log, TEXT("Hello from game mode"));
	PlayerControllerClass = AMousePlayerController::StaticClass();
	HUDClass = ABaseHUD::StaticClass();
}

void AMolVizGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	RepresentationFactory = NewObject<URepresentationFactory>(this);
	/*ProteinReps.Add(
		TWeakObjectPtr<AProteinRepresentation>(
				
						Cast<AProteinRepresentation>(GetWorld()->SpawnActor(
							AProteinRepresentation::StaticClass()
						)
					)
			)
	);*/
	//Cast<AMousePlayerController>(UGameplayStatics::GetPlayerController(this, 0))->ProteinRep = ProteinReps[0];
	//Proteins.Add(TWeakObjectPtr<AProteinData>(Cast<AProteinData>(GetWorld()->SpawnActor((AProteinData::StaticClass())))));
	//ProteinData->LoadCompleteDelegate.AddUFunction(this, "OnLoadComplete");
	//Cast<AProteinRepresentation>(Protein)->AddAtom(10, 10, 10);
	//UE_LOG(LogTemp, Log, TEXT("Hello from game mode"));
}

TWeakObjectPtr<AProteinData> AMolVizGameModeBase::CreateNewProteinData()
{
	return this->Proteins[
		this->Proteins.Add(
		TWeakObjectPtr<AProteinData>(
				Cast<AProteinData>(
					GetWorld()->SpawnActor(AProteinData::StaticClass()
					)
				)
			)
		)
	];
}

void AMolVizGameModeBase::SelectionChanged(const TWeakObjectPtr<AProteinData>& ProteinRep)
{
	Cast<AMousePlayerController>(UGameplayStatics::GetPlayerController(this, 0))->SetProteinRep(ProteinRep.Get()->Representation.Get());
}

void AMolVizGameModeBase::OnLoadComplete(AProteinData * ProteinData)
{
	int Index = ProteinReps.Add(
		TWeakObjectPtr<AProteinRepresentation>(
			Cast<AProteinRepresentation>(GetWorld()->SpawnActor(
				AProteinRepresentation::StaticClass()
			)
				)
			)
	);
	ProteinReps[Index]->SetActorLocation(ProteinData->FindCOM());
	ProteinData->Representation = ProteinReps[Index];
	RepresentationFactory->CreateNewVdwRep(ProteinData, "VDW");
	Cast<AMousePlayerController>(UGameplayStatics::GetPlayerController(this, 0))->SetProteinRep(ProteinReps[Index].Get());
}
