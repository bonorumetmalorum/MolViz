// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FColorData.h"
#include "FResidue.h"
#include "Engine/DataTable.h" 
#include "Representation.generated.h"
//forward declaration
class AProteinData;
/*
 * 3d representation of a molecule in the scene, inherited from all such representations
 */
UCLASS(ClassGroup=(Representation), Abstract)
class MOLVIZ_API URepresentation : public USceneComponent
{
	GENERATED_BODY()

public:
	URepresentation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*
	 * convert the atoms name to an atom element
	 * @param name the atoms name
	 * @return the atoms element
	 */
	static AtomType NameToType(FString name);

	UDataTable* AtomColors;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/*
	 * create the representation
	 * @param ProteinData the protein data to represent in the scene
	 */
	virtual void ConstructRepresentation(AProteinData * ProteinData);
};
