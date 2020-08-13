// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProteinRepresentation.generated.h"
/*
 * this class represents one protein / chain representation
 * it will have a root for each chain
 * each residue will have a root 
 * It will have many residues
 * residues will have many atoms
 */

//create delegates for
/*
 * update representation selection
 */

class URepresentation;

class AProteinData;
USTRUCT()
struct FRepOptions
{
	GENERATED_BODY()
};

UCLASS()
class MOLVIZ_API AProteinRepresentation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProteinRepresentation();
	FString FileName;
	//make methods to activate / deactive a representation
	/*
	 * activates a representation
	 * @param Rep representation to activate
	 */
	void ActivateRepresentation(TWeakObjectPtr<URepresentation> Rep);
	/*
	 * deactivates a representation
	 * @param Rep representation to deactivate
	 */
	void DeactivateRepresentation(TWeakObjectPtr<URepresentation> Rep);
	/*
	 * removes a representation
	 * @param Representation representation to remove
	 */
	void RemoveRep(const TWeakObjectPtr<URepresentation> Representation);

	TArray<TWeakObjectPtr<URepresentation>> Representations;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
