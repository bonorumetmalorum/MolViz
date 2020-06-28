// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AProteinData.h"
#include "AppManager.generated.h"

/**
 * App instance manages everything the app has to keep track off
 * this includes instances of proteins in a macro molecule for example
 * at the moment it will keep track of one protein / chain
 *
 *
 *
 * DO WE NEED THIS CLASS. MIGHT AS WELL JUST USE THE GAME MODE BASE CLASS
 */
UCLASS()
class MOLVIZ_API UAppManager : public UGameInstance
{
	GENERATED_BODY()
public:
	AProteinData* ProteinData;
	void Init() override;
};
