// Fill out your copyright notice in the Description page of Project Settings.


#include "SFileExplorer.h"
#include "SlateOptMacros.h"


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
	float widgetWidth = 5.0f;
	FString button = FString("hello");
	TSharedPtr<SWindow> mainWindow;
	ChildSlot
	[
		/*SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Top)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Black)
			]
			+SHorizontalBox::Slot()
			[
				SNew(SBorder)
				.BorderBackgroundColor(FSlateColor(FLinearColor::Black))
				[
					SNew(SButton)
					.Text(FText::FromString(button))
				]
			]
		]*/
		SAssignNew(mainWindow, SWindow)
		.MaxWidth(widgetWidth)
		.MaxHeight(widgetWidth)
		.FocusWhenFirstShown(true)
		.SupportsTransparency(FWindowTransparency(EWindowTransparency::PerWindow))
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
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
