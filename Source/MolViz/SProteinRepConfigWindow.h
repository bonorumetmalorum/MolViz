// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProteinRepresentation.h"
#include "RepresentationFactory.h"
#include "Widgets/SCompoundWidget.h"

class URepresentation;

/**
 * UI window to show and configure representations for a selected protein
 */
class MOLVIZ_API SProteinRepConfigWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SProteinRepConfigWindow){}
	SLATE_ARGUMENT(TWeakObjectPtr<AProteinData>, Protein)
	SLATE_ARGUMENT(TWeakObjectPtr<URepresentationFactory>, RepFactory)
	SLATE_END_ARGS()

	/**
	 * Constructs this widget with InArgs
	 * @param InArgs the arugments to setup the UI
	 */
	void Construct(const FArguments& InArgs);
	/**
	 * display a new row in the table of represenations
	 * @param Rep the representation to display
	 * @param OwnerTable the table for displaying
	 * @return the newly created row
	 */
	TSharedRef<ITableRow> GenerateRepRow(TWeakObjectPtr<URepresentation> Rep, const TSharedRef<STableViewBase>& OwnerTable);

	/**
	 * hide a selected representation
	 * @param selected representation
	 */
	void HideRep(TWeakObjectPtr<URepresentation> Rep);
	
private:
	TSharedPtr<SListView<TWeakObjectPtr<URepresentation>>> RepresentationsView;
	TWeakObjectPtr<URepresentationFactory> RepFactory;
	TWeakObjectPtr<AProteinData> ProteinData;
	TWeakObjectPtr<URepresentation> SelectedRep;
	FReply RemoveRepresentation();

	FReply AddNewCpk();
	FReply AddNewVdw();
	FReply AddNewTube();
	FReply AddNewNCartoon();
	void SelectionChanged(TWeakObjectPtr<URepresentation> ProteinRep, ESelectInfo::Type SelectionInfo);
};
