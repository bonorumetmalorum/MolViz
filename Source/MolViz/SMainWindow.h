// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "FPdbReader.h"
#include "MolVizGameModeBase.h"

DECLARE_EVENT_OneParam(SMainWindow, FAddProteinRepEvent, AProteinData*)

DECLARE_EVENT_OneParam(SMainWindow, FProteinDataLoadComplete, AProteinData*)

/**
 * File explorer ui to be used to load PDB and DCD files from the system in game
 */
class MOLVIZ_API SMainWindow : public SCompoundWidget
{

public:

	SLATE_BEGIN_ARGS(SMainWindow) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMolVizGameModeBase>, AppManager)

	SLATE_ARGUMENT(TArray< TWeakObjectPtr<AProteinData>>*, Proteins)

	SLATE_END_ARGS()

	FReply OpenFileDialog();
	
	void Construct(const FArguments& InArgs);

	TSharedRef<ITableRow> CreateListItem(TWeakObjectPtr<AProteinData> Item, const TSharedRef<STableViewBase>& OwnerTable);

	FReply AddNewRepresentation() const;
	
private:
	TArray <TWeakObjectPtr<AProteinData>> * Proteins;
	TSharedPtr<SWindow> MainWindow;
	FPdbReader PDBReader;
	FSSReader SSReader;
	TWeakObjectPtr<class AMolVizGameModeBase> AppManager;
	TWeakObjectPtr<AProteinData> SelectedProtein;

public:
	//EVENTS
	FAddProteinRepEvent NewProteinRep;
	FProteinDataLoadComplete ProteinDataLoadComplete;
};