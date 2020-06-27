// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AProteinData.h"
#include "AppManager.generated.h"

/**
 * 
 */
UCLASS()
class MOLVIZ_API UAppManager : public UGameInstance
{
	GENERATED_BODY()
public:
	AProteinData* ProteinData;
	void Init() override;
};
