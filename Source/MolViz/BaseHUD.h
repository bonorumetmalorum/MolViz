// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HAL/FileManagerGeneric.h"
#include "SMainWindow.h"
#include "MolViz.h"
#include "BaseHUD.generated.h"


/**
 * 
 */
UCLASS()
class MOLVIZ_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	TWeakObjectPtr<FFileManagerGeneric> fileManager;
	TSharedPtr<SMainWindow> fileExplorer;
	TSharedPtr<SWidget> container;
};
