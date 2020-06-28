// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAtom.h"
#include "FBondData.h"
#include "FResidue.h"
#include "GameFramework/Info.h"
#include "AProteinData.generated.h"

DECLARE_EVENT(AProteinData, FLoadComplete)

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

	void LoadComplete();
	void CreateBonds();
	void AddResidue(FString Resname, int32 Resnum);
	void AddAtom(int32 Snum, uint8 Alt, uint8 Chain, int32 Resnum, uint8 Insertion_residue_code, FVector position, float Occupancy, float TempFactor, FString Element);
	TArray<FAtomData> Atoms;
	TArray<FResidue> Residues;
	TArray<FBondData> Bonds;
	void BeginPlay() override;
	FLoadComplete LoadCompleteDelegate;
};
