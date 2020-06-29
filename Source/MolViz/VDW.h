// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Representation.h"
#include "VDW.generated.h"

/**
 * 
 */
UCLASS()
class MOLVIZ_API UVDW : public URepresentation
{
	GENERATED_BODY()

public:
	UVDW();
	void ConstructRepresentation(TArray<FResidue>& residues) override;
};
