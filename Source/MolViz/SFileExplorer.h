// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "HAL/FileManagerGeneric.h"

/**
 * File explorer ui to be used to load PDB and DCD files from the system in game
 */
class MOLVIZ_API SFileExplorer : public SCompoundWidget
{

public:

	SLATE_BEGIN_ARGS(SFileExplorer) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class FFileManagerGeneric>, fileManager)
		
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
};
