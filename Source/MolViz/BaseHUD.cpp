// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"
#include "SMainWindow.h"
#include "Widgets/SWeakWidget.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine && GEngine->GameViewport)
	{ //if we have a game instance and viewport to add UI elements to
		fileExplorer = SNew(SMainWindow) //create a new main window
		.AppManager(TWeakObjectPtr<AMolVizGameModeBase>(Cast<AMolVizGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))) //set the app manager instance
		.Proteins(&Cast<AMolVizGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->Proteins); //set the list of loaded proteins
	}
}