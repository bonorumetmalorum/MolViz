// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "pdbio.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MOLVIZ_API Updbio : public UObject
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "IO")
	void readPDB();

private:

};
