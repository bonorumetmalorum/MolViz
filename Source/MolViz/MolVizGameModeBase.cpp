// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "MolVizGameModeBase.h"

#include "MousePlayerController.h"
#include "Protein.h"

AMolVizGameModeBase::AMolVizGameModeBase() : Super()
{
	UE_LOG(LogTemp, Log, TEXT("Hello from game mode"));
	HUDClass = ABaseHUD::StaticClass();
	PlayerControllerClass = AMousePlayerController::StaticClass();
}

void AMolVizGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Protein = GetWorld()->SpawnActor((AProtein::StaticClass()));
	Cast<AProtein>(Protein)->AddAtom(10, 10, 10);
	//UE_LOG(LogTemp, Log, TEXT("Hello from game mode"));
}
