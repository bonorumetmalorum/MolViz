// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAtom.h"
#include "FResidue.h"
#include "GameFramework/Info.h"
#include "AProteinData.generated.h"

/**
 * holds residue information and all atoms in this protein
 */
UCLASS()
class MOLVIZ_API AProteinData : public AInfo
{
	GENERATED_BODY()
public:
	AProteinData();
	~AProteinData();

	void CreateBonds();
	void AddAtom(int32 Snum, uint8 Alt, uint8 Chain, int32 Resnum, uint8 Insertion_residue_code, FVector position, float Occupancy, float TempFactor, FString Element);
	TArray<FAtomData> Atoms;
	TArray<FResidue> Residues;

	void BeginPlay() override;
};
