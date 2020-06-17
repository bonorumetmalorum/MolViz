// Fill out your copyright notice in the Description page of Project Settings.


#include "SFileExplorer.h"
#include "SlateOptMacros.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "DesktopPlatform/Public/IDesktopPlatform.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SFileExplorer::Construct(const FArguments& InArgs)
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
		.Title(FText::FromString(FString("File Explorer")))
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SImage)
					.ColorAndOpacity(FColor::Black)
				]
				+SVerticalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromString(button))
					.OnClicked(this, &SFileExplorer::OpenFileDialog)
				]
			]
		]
	];
	FSlateApplication::Get().AddWindow(MainWindow.ToSharedRef());

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SFileExplorer::OpenFileDialog()
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
			PDBReader.read(Element);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("dialog closed with no selections"));
	}
	
	return FReply::Handled();
}