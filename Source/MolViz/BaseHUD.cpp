// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"
#include "Widgets/SWeakWidget.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Hello world"));
	if (GEngine && GEngine->GameViewport)
	{
		fileExplorer = SNew(SFileExplorer).fileManager(fileManager);
	}
}