// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProteinRepresentation.generated.h"
/*
 * this class represents one protein / chain representation
 * it will have a root for each 
 * It will have many residues
 * residues will have many atoms
 */

//create delegates for
/*
 * update representation selection
 */
UCLASS()
class MOLVIZ_API AProteinRepresentation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProteinRepresentation();
	void AddAtom(float x, float y, float z);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
