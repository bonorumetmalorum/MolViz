// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MolViz.h"
#include "BaseHUD.generated.h"
//forward declaration
class SMainWindow;

/**
 * Class to manage UI context
 * sets up the UI and initializes all of its variables
 */
UCLASS()
class MOLVIZ_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

protected:

	void BeginPlay() override;

	TSharedPtr<SMainWindow> fileExplorer;
	TSharedPtr<SWidget> container;
};
