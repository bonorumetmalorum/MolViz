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
	virtual void ConstructRepresentation(AProteinData* ProteinData/*, FColourScheme ColourScheme*/) override; //TODO IMPLEMENT COLOUR SCHEME
	void AddTubeSection( FAtomData* StartAtom,  FAtomData* ControlAtom,  FAtomData* EndAtom);
	void AddTubeSection( FAtomData* StartAtom,  FAtomData* StartControlAtom,  FAtomData* EndControlAtom,
							FAtomData* EndAtom);
};
