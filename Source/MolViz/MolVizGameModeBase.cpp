// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "MolVizGameModeBase.h"

AMolVizGameModeBase::AMolVizGameModeBase() : Super()
{
	UE_LOG(LogTemp, Log, TEXT("Hello from game mode"));
	HUDClass = ABaseHUD::StaticClass();
}

void AMolVizGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Log, TEXT("Hello from game mode"));
}
