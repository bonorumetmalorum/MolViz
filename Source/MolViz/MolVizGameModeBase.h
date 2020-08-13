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
 */
UCLASS()
class MOLVIZ_API AMolVizGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMolVizGameModeBase();
	/*
	 * called at the start of the level
	 */
	virtual void BeginPlay() override;
	/*
	 * creates a new protein data instance
	 * @return ptr to a newly created protein data
	 */
	TWeakObjectPtr<AProteinData> CreateNewProteinData();
	/*
	 * method to handle UI event selection change on protein
	 * @param ProteinRep the protein representation selected
	 */
	void SelectionChanged(const TWeakObjectPtr<AProteinData>& ProteinRep);
	/*
	 * destroys a molecule
	 * @param Molecule molecule that will be destroyed
	 */
	void DestroyMolecule(TWeakObjectPtr<AProteinData> Molecule);


	TArray<TWeakObjectPtr<AProteinRepresentation>> ProteinReps;
	TArray<TWeakObjectPtr<AProteinData>> Proteins;
	UPROPERTY()
	URepresentationFactory * RepresentationFactory = nullptr;
	/*
	 * handle load complete, setup protein data
	 * @param ProteinData the protein data that was just read in
	 */
	UFUNCTION()
	void OnLoadComplete(AProteinData * ProteinData);
};
