// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AProteinData.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseHUD.h"
#include "RepresentationFactory.h"

#include "MolVizGameModeBase.generated.h"

/**
 * Bootstrapping class. Used to setup the main context and UI
 * we need to add a protein actor to the scene so we can add atom and bond components to it
 */
UCLASS()
class MOLVIZ_API AMolVizGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMolVizGameModeBase();
	virtual void BeginPlay() override;

	
	TArray<TWeakObjectPtr<AProteinRepresentation>> ProteinReps;
	UPROPERTY()
	AProteinData* ProteinData = nullptr;
	UPROPERTY()
	URepresentationFactory * RepresentationFactory = nullptr;
	UFUNCTION()
	void OnLoadComplete() const;
};
