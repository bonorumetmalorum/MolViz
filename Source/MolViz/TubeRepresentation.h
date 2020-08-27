// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Representation.h"
#include "TubeRepresentation.generated.h"

/**
 * 
 */
UCLASS()
class MOLVIZ_API UTubeRepresentation : public URepresentation
{
	GENERATED_BODY()

public:
	virtual void ConstructRepresentation(AProteinData* ProteinData) override;
	void AddTubeSection( FAtomData* StartAtom,  FAtomData* ControlAtom,  FAtomData* EndAtom);
	void AddTubeSection(FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
};
