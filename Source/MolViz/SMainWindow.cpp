// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainWindow.h"
#include "Slate/Private/Framework/MultiBox/SMenuEntryBlock.h"
#include "MolVizGameModeBase.h"
#include "SlateOptMacros.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "DesktopPlatform/Public/IDesktopPlatform.h"
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
						SAssignNew(ProteinListView, SListView<TWeakObjectPtr<AProteinData>>)
						.ListItemsSource(Proteins)
						.OnGenerateRow(this, &SMainWindow::CreateListItem)
						.SelectionMode(ESelectionMode::Single)
						.OnSelectionChanged(this, &SMainWindow::SelectionChanged)
					]	
				+ SVerticalBox::Slot()
					[
						SNew(SButton)
						.Text(FText::FromString("Add Representation"))
						.OnClicked(this, &SMainWindow::AddNewRepresentation)
					]
				+ SVerticalBox::Slot()
					[
						SNew(SButton)
						.Text(FText::FromString("Remove Molecule"))
						.OnClicked(this, &SMainWindow::RemoveMolecule)
					]
				]
			]
	];
	FSlateApplication::Get().AddWindow(MainWindow.ToSharedRef());

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

//TODO I need to allow for file type recognition, and switching to parse DSSP / PDB info.
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
			ProteinListView->RequestListRefresh();
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
	return SNew(STableRow<TWeakObjectPtr<AProteinData>>, OwnerTable)
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString(Item->FilePath))
		];
}

FReply SMainWindow::AddNewRepresentation()
{
	//NewProteinRep.Broadcast(SelectedProtein.Get());
	//add a new representation
	if (SelectedProtein.IsValid())
	{
		//SAssignNew(ProteinRepWindow, SProteinRepConfigWindow).ProteinRep(this->SelectedProtein->Representation);
		SAssignNew(ProteinRepWindow, SWindow)
		.Title(FText::FromString("HELLO"))
		.MinWidth(400)
		.MinHeight(400)
		[
			SNew(SProteinRepConfigWindow)
			.Protein(this->SelectedProtein)
			.RepFactory(TWeakObjectPtr<URepresentationFactory>(this->AppManager->RepresentationFactory))
		];
		FSlateApplication::Get().AddWindowAsNativeChild(ProteinRepWindow.ToSharedRef(), MainWindow.ToSharedRef());
	}		
	else
		UE_LOG(LogTemp, Warning, TEXT("Unable to open rep config window because no protein was selected"));
	return FReply::Handled();
}

void SMainWindow::SelectionChanged(TWeakObjectPtr<AProteinData> ProteinData, ESelectInfo::Type SelectionInfo)
{
	this->SelectedProtein = ProteinData;
	AppManager->SelectionChanged(SelectedProtein);
}

FReply SMainWindow::RemoveMolecule() const
{
	AppManager->DestroyMolecule(SelectedProtein);
	ProteinListView->RequestListRefresh();
	return FReply::Handled();
}
