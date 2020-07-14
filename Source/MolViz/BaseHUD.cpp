// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"
#include "SMainWindow.h"
#include "Widgets/SWeakWidget.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine && GEngine->GameViewport)
	{
		fileExplorer = SNew(SMainWindow)
		.AppManager(TWeakObjectPtr<AMolVizGameModeBase>(Cast<AMolVizGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))))
		.Proteins(&Cast<AMolVizGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->ProteinReps);
	}
}