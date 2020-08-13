// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "FPdbReader.h"
#include "MolVizGameModeBase.h"
#include "SProteinRepConfigWindow.h"

DECLARE_EVENT_OneParam(SMainWindow, FAddProteinRepEvent, AProteinData*)

DECLARE_EVENT_OneParam(SMainWindow, FProteinDataLoadComplete, AProteinData*)

/**
 * File explorer ui to be used to load PDB and DCD / XTC files from the system in game
 */
class MOLVIZ_API SMainWindow : public SCompoundWidget
{

public:

	//setting arguments / fields for the UI
	SLATE_BEGIN_ARGS(SMainWindow) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMolVizGameModeBase>, AppManager)

	SLATE_ARGUMENT(TArray< TWeakObjectPtr<AProteinData>>*, Proteins)

	SLATE_END_ARGS()

	/*
	 * method to handle opening the file dialog
	 */
	FReply OpenFileDialog();
	/*
	 * construct the UI
	 * @param InArgs the arguments rquired to setup the UI
	 */
	void Construct(const FArguments& InArgs);

	/*
	 * create a new list item to display in the UI
	 * @param Item the item to display
	 * @param OwnderTable the table in which it will be displayed
	 * @return a reference to the newly created row
	 */
	TSharedRef<ITableRow> CreateListItem(TWeakObjectPtr<AProteinData> Item, const TSharedRef<STableViewBase>& OwnerTable);
	/*
	 * add a new representation
	 */
	FReply AddNewRepresentation();
	/*
	 * process selection changed event
	 * @param ProteinData protein data that the selection has changed to
	 * @param SelectionInfo the type of selection that was made
	 */
	void SelectionChanged(TWeakObjectPtr<AProteinData> ProteinData, ESelectInfo::Type SelectionInfo);

private:
	TArray <TWeakObjectPtr<AProteinData>> * Proteins;
	TSharedPtr<SWindow> MainWindow;
	FPdbReader PDBReader;
	FSSReader SSReader;
	TWeakObjectPtr<class AMolVizGameModeBase> AppManager;
	TWeakObjectPtr<AProteinData> SelectedProtein;
	TSharedPtr<SListView<TWeakObjectPtr<AProteinData>>> ProteinListView;
	TSharedPtr<SWindow> ProteinRepWindow;
	FReply RemoveMolecule() const;

public:
	//EVENTS
	FAddProteinRepEvent NewProteinRep;
	FProteinDataLoadComplete ProteinDataLoadComplete;
};