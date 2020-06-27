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
	void AddAtom(float X, float Y, float Z);
	TArray<FAtomData> Atoms;
	TArray<FResidue> Residues;

	void BeginPlay() override;
};
