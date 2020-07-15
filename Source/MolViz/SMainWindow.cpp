// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainWindow.h"
#include "Slate/Private/Framework/MultiBox/SMenuEntryBlock.h"
#include "MolVizGameModeBase.h"
#include "SlateOptMacros.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "DesktopPlatform/Public/IDesktopPlatform.h"
#include "ProteinRepresentation.h"
#include "Slate/Private/Framework/MultiBox/SClippingHorizontalBox.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainWindow::Construct(const FArguments& InArgs)
{
	/*
	 * We need to create a UI where we have
	 * an x button in the corner to cancel loading
	 * click and drag functionality
	 * a button to navigate up one level
	 * a list view of the current directory
	 */
	float widgetWidth = 500.0f;
	FString button = FString("select a file");
	AppManager = InArgs._AppManager;
	Proteins = InArgs._Proteins;
	bCanTick = true;
	ChildSlot
	[

		SAssignNew(MainWindow, SWindow)
		/*.MaxWidth(widgetWidth)
		.MaxHeight(widgetWidth)*/
		.IsInitiallyMaximized(false)
		.SizingRule(ESizingRule::UserSized)
		.MinHeight(widgetWidth)
		.MinWidth(widgetWidth)
		.FocusWhenFirstShown(true)
		.FocusWhenFirstShown(true)
		.SupportsTransparency(FWindowTransparency(EWindowTransparency::PerWindow))
		.RenderOpacity(0.5f)
		.SupportsMinimize(false)
		.SupportsMaximize(false)
		.Title(FText::FromString(FString("MolViz")))
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SOverlay)
					+SOverlay::Slot()
					[
						SNew(SBox)
						[
							SNew(SMenuOwner)
							[
								SNew(SHorizontalBox)
								+SHorizontalBox::Slot()
								[
									SNew(SVerticalBox)
									+ SVerticalBox::Slot()
									[
										SNew(SButton)
										.Text(FText::FromString("Open PDB"))
										.OnClicked(this, &SMainWindow::OpenFileDialog)
									]
								]
								+SHorizontalBox::Slot()
								[
									SNew(SVerticalBox)
									+ SVerticalBox::Slot()
									[
										SNew(SButton)
										.Text(FText::FromString("Open XTC"))
									]
								]
							]
						]
					]
				]
				+ SVerticalBox::Slot()
					[
						SNew(SListView<TWeakObjectPtr<AProteinData>>)
						.ListItemsSource(Proteins)
						.OnGenerateRow(this, &SMainWindow::CreateListItem)
						.SelectionMode(ESelectionMode::Single)
					]	
				+ SVerticalBox::Slot()
					[
						SNew(SButton)
						.Text(FText::FromString("Add Representation"))
						.OnClicked(this, &SMainWindow::AddNewRepresentation)
					]
				]
			]
	];
	FSlateApplication::Get().AddWindow(MainWindow.ToSharedRef());

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

//TODO I need to allow for file type recognition, and switching to parse DSSP / PDB info.
//TODO I also need to create a list of protein datas rather than a single one and pass the list in here, adding a new one
//TODO I also need to reconsider storing a reference to the AtomData instead of teh ProteinRep in the UI.
FReply SMainWindow::OpenFileDialog()
{
	IDesktopPlatform * Platform = FDesktopPlatformModule::Get();
	TArray<FString> Filenames;
	const bool bResult = Platform->OpenFileDialog(
		MainWindow.Get()->GetNativeWindow()->GetOSWindowHandle(),
		FString("Select a file"),
		FString("/"),
		FString(""),
		FString(""),
		EFileDialogFlags::None,
		Filenames
	);
	if(bResult)
	{
		for(auto Element : Filenames)
		{
			
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, Element);
			TWeakObjectPtr<AProteinData> ProteinData = this->AppManager->CreateNewProteinData();
			PDBReader.readStructure(Element, ProteinData.Get());
			SSReader.readStructure(Element, ProteinData.Get());
			//broadcast the event
			//ProteinDataLoadComplete.Broadcast(ProteinData.Get());
			AppManager->OnLoadComplete(ProteinData.Get());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("dialog closed with no selections"));
	}
	
	return FReply::Handled();
}

TSharedRef<ITableRow> SMainWindow::CreateListItem(TWeakObjectPtr<AProteinData> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<TSharedPtr<AProteinRepresentation>>, OwnerTable)
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString(Item->GetName()))
		];
}

FReply SMainWindow::AddNewRepresentation() const
{
	//NewProteinRep.Broadcast(SelectedProtein.Get());
	//add a new representation
	return FReply::Handled();
}
