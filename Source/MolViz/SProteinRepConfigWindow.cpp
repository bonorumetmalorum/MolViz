// Fill out your copyright notice in the Description page of Project Settings.


#include "SProteinRepConfigWindow.h"
#include "Representation.h"
#include "AProteinData.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SProteinRepConfigWindow::Construct(const FArguments& InArgs)
{
	this->ProteinData = InArgs._Protein;
	this->RepFactory = InArgs._RepFactory;
	ChildSlot
	[
		SNew(SOverlay)
		+SOverlay::Slot()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				SNew(SBox)
				.Content()
				[
					SAssignNew(RepresentationsView, SListView<TWeakObjectPtr<URepresentation>>)
					.ListItemsSource(&this->ProteinData->GetRepresentation()->Representations)
					.OnGenerateRow(this, &SProteinRepConfigWindow::GenerateRepRow)
					.OnMouseButtonDoubleClick(this, &SProteinRepConfigWindow::HideRep)
					.OnSelectionChanged(this, &SProteinRepConfigWindow::SelectionChanged)
				]
			]
			+SVerticalBox::Slot()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromString("Add New CPK"))
					.OnClicked(this, &SProteinRepConfigWindow::AddNewCpk)
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromString("Add New VDW"))
					.OnClicked(this, &SProteinRepConfigWindow::AddNewVdw)
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromString("Add New Tube"))
					.OnClicked(this, &SProteinRepConfigWindow::AddNewTube)
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromString("Add New New Cartoon"))
					.OnClicked(this, &SProteinRepConfigWindow::AddNewNCartoon)
				]
			]
			+SVerticalBox::Slot()
			[
				SNew(SButton)
				.Text(FText::FromString("Remove Representation"))
				.OnClicked(this, &SProteinRepConfigWindow::RemoveRepresentation)
			]
		]
	];
	
}

TSharedRef<ITableRow> SProteinRepConfigWindow::GenerateRepRow(TWeakObjectPtr<URepresentation> Rep,
	const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<TWeakObjectPtr<AProteinData>>, OwnerTable)
		.Content()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			[
				SNew(STextBlock)
				.Text(FText::FromString(Rep->GetName()))
			]
		];
}

void SProteinRepConfigWindow::HideRep(TWeakObjectPtr<URepresentation> Rep)
{
	Rep->SetHiddenInGame(!Rep->bHiddenInGame, true);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SProteinRepConfigWindow::RemoveRepresentation()
{
	ProteinData->GetRepresentation()->RemoveRep(SelectedRep);
	this->RepresentationsView->RequestListRefresh();
	return FReply::Handled();
}

FReply SProteinRepConfigWindow::AddNewCpk()
{
	this->RepFactory->CreateNewCpkRep(this->ProteinData.Get()->GetRepresentation().Get(), this->ProteinData.Get(), FName("CPK"));
	this->RepresentationsView->RequestListRefresh();
	return FReply::Handled();
}

FReply SProteinRepConfigWindow::AddNewVdw()
{
	this->RepFactory->CreateNewVdwRep(this->ProteinData.Get(), FName("VDW"));
	this->RepresentationsView->RequestListRefresh();
	return FReply::Handled();
}

FReply SProteinRepConfigWindow::AddNewTube()
{
	this->RepFactory->CreateNewTubeRep(this->ProteinData.Get()->GetRepresentation().Get(), this->ProteinData.Get(), FName("TUBE"));
	this->RepresentationsView->RequestListRefresh();
	return FReply::Handled();
}

FReply SProteinRepConfigWindow::AddNewNCartoon()
{
	this->RepFactory->CreateNewNCartoonRep(this->ProteinData.Get()->GetRepresentation().Get(), this->ProteinData.Get(), FName("NCARTOON"));
	this->RepresentationsView->RequestListRefresh();
	return FReply::Handled();
}

void SProteinRepConfigWindow::SelectionChanged(TWeakObjectPtr<URepresentation> ProteinRep, ESelectInfo::Type SelectionInfo)
{
	this->SelectedRep = ProteinRep;
}