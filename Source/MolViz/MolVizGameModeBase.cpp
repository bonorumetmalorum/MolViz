// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "MolVizGameModeBase.h"

#include "MousePlayerController.h"
#include "ProteinRepresentation.h"

AMolVizGameModeBase::AMolVizGameModeBase() : Super()
{
	UE_LOG(LogTemp, Log, TEXT("Hello from game mode"));
	HUDClass = ABaseHUD::StaticClass();
	PlayerControllerClass = AMousePlayerController::StaticClass();
}

void AMolVizGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ProteinRepresentation = GetWorld()->SpawnActor((AProteinRepresentation::StaticClass()));
	ProteinData = Cast<AProteinData>(GetWorld()->SpawnActor((AProteinData::StaticClass())));
	ProteinData->LoadCompleteDelegate.AddUFunction(ProteinRepresentation, "CreateNewRepresentation");
	//Cast<AProteinRepresentation>(Protein)->AddAtom(10, 10, 10);
	//UE_LOG(LogTemp, Log, TEXT("Hello from game mode"));
}
