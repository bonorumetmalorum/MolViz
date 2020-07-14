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
			SNew(SListView<TWeakObjectPtr<AProteinRepresentation>>)
			.ListItemsSource(Proteins)
			.OnGenerateRow(this, &SMainWindow::CreateListItem)
			.SelectionMode(ESelectionMode::Single)
				]
			]
		]
	];
	FSlateApplication::Get().AddWindow(MainWindow.ToSharedRef());

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

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
		EFileDialogFlags::Multiple,
		Filenames
	);
	if(bResult)
	{
		for(auto Element : Filenames)
		{
			
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, Element);
			PDBReader.readStructure(Element, this->AppManager->ProteinData);
			SSReader.readStructure(Element, this->AppManager->ProteinData);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("dialog closed with no selections"));
	}
	
	return FReply::Handled();
}

TSharedRef<ITableRow> SMainWindow::CreateListItem(TWeakObjectPtr<AProteinRepresentation> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<TSharedPtr<AProteinRepresentation>>, OwnerTable)
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString(Item->GetName()))
		];
}
