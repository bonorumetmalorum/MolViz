// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Representation.h"
#include "NewCartoonRepresentation.generated.h"

/**
 * 
 */
UCLASS()
class MOLVIZ_API UNewCartoonRepresentation : public URepresentation
{
	GENERATED_BODY()

	void ConstructRepresentation(AProteinData* ProteinData) override;
	
};
