// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "HAL/FileManagerGeneric.h"
#include "FPdbReader.h"

/**
 * File explorer ui to be used to load PDB and DCD files from the system in game
 */
class MOLVIZ_API SMainWindow : public SCompoundWidget
{

public:

	SLATE_BEGIN_ARGS(SMainWindow) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class FFileManagerGeneric>, fileManager)

	SLATE_END_ARGS()

	FReply OpenFileDialog();
	
	void Construct(const FArguments& InArgs);	
private:
	TSharedPtr<SWindow> MainWindow;
	FPdbReader PDBReader;
};