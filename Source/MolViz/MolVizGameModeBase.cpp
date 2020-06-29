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
	RepresentationFactory = NewObject<URepresentationFactory>(this);
	ProteinRepresentation = GetWorld()->SpawnActor((AProteinRepresentation::StaticClass()));
	ProteinData = Cast<AProteinData>(GetWorld()->SpawnActor((AProteinData::StaticClass())));
	ProteinData->LoadCompleteDelegate.AddUFunction(this, "OnLoadComplete");
	//Cast<AProteinRepresentation>(Protein)->AddAtom(10, 10, 10);
	//UE_LOG(LogTemp, Log, TEXT("Hello from game mode"));
}

void AMolVizGameModeBase::OnLoadComplete() const
{
	RepresentationFactory->CreateNewVdwRep(Cast<AProteinRepresentation>(ProteinRepresentation), ProteinData, "VDW");
}
