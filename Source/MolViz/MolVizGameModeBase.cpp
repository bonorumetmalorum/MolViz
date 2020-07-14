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
	ProteinReps.Add(
		TWeakObjectPtr<AProteinRepresentation>(
				
						Cast<AProteinRepresentation>(GetWorld()->SpawnActor(
							AProteinRepresentation::StaticClass()
						)
					)
			)
	);
	Cast<AMousePlayerController>(UGameplayStatics::GetPlayerController(this, 0))->ProteinRep = ProteinReps[0];
	ProteinData = Cast<AProteinData>(GetWorld()->SpawnActor((AProteinData::StaticClass())));
	ProteinData->LoadCompleteDelegate.AddUFunction(this, "OnLoadComplete");
	//Cast<AProteinRepresentation>(Protein)->AddAtom(10, 10, 10);
	//UE_LOG(LogTemp, Log, TEXT("Hello from game mode"));
}

void AMolVizGameModeBase::OnLoadComplete() const
{
	RepresentationFactory->CreateNewCpkRep(ProteinReps[0].Get(), ProteinData, "CPK");
}
