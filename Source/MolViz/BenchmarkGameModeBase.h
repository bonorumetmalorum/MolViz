// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPdbReader.h"
#include "ProteinRepresentation.h"
#include "SSReader.h"
#include "GameFramework/GameModeBase.h"
#include "BenchmarkGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MOLVIZ_API ABenchmarkGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void AddProtein();
	void Reset();
	

private:
	FPdbReader Reader;
	FSSReader SSReader;
	TArray<AProteinRepresentation> ProteinReps;
};
