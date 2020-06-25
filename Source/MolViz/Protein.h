// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Protein.generated.h"
/*
 * this class represents one protein / chain
 * It will have many residues
 * residues will have many atoms
 */
UCLASS()
class MOLVIZ_API AProtein : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProtein();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AddAtom(float x, float y, float z);

};
