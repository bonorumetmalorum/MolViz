// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FResidue.h"
#include "Representation.generated.h"


class AProteinData;
UCLASS(ClassGroup=(Representation), Abstract)
class MOLVIZ_API URepresentation : public USceneComponent
{
	GENERATED_BODY()

public:
	URepresentation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//create the representation
	virtual void ConstructRepresentation(AProteinData * ProteinData/*, FColourScheme ColourScheme*/); //TODO IMPLEMENT COLOUR SCHEME
	/*virtual void UpdateRepresentation() = 0;*/ //TODO implement this when UI is in progress
};
