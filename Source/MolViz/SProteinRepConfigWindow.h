// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProteinRepresentation.h"
#include "RepresentationFactory.h"
#include "Widgets/SCompoundWidget.h"

class URepresentation;

/**
 * 
 */
class MOLVIZ_API SProteinRepConfigWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SProteinRepConfigWindow){}
	SLATE_ARGUMENT(TWeakObjectPtr<AProteinData>, Protein)
	SLATE_ARGUMENT(TWeakObjectPtr<URepresentationFactory>, RepFactory)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TSharedRef<ITableRow> GenerateRepRow(TWeakObjectPtr<URepresentation> Rep, const TSharedRef<STableViewBase>& OwnerTable);
	
private:
	TSharedPtr<SListView<TWeakObjectPtr<URepresentation>>> RepresentationsView;
	TWeakObjectPtr<URepresentationFactory> RepFactory;
	TWeakObjectPtr<AProteinData> ProteinData;

	FReply AddNewCpk();
	FReply AddNewVdw();
	FReply AddNewTube();
	FReply AddNewNCartoon();
};
