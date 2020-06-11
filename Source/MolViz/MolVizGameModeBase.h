// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseHUD.h"
#include "MolVizGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MOLVIZ_API AMolVizGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMolVizGameModeBase();
	virtual void BeginPlay() override;
};
