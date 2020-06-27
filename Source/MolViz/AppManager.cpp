// Fill out your copyright notice in the Description page of Project Settings.


#include "AppManager.h"

void UAppManager::Init()
{
	Super::Init();
	ProteinData = Cast<AProteinData>(GetWorld()->SpawnActor(AProteinData::StaticClass()));
}
