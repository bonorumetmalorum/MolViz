// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPdbReader.h"
#include "ProteinRepresentation.h"
#include "AProteinData.h"
#include "RepresentationFactory.h"
#include "SSReader.h"
#include "GameFramework/GameModeBase.h"
#include "BenchmarkGameModeBase.generated.h"

/**
 * this game mode acts as a benchmark
 * it should load a pdb
 * make copies of the pdb until we reach the upper limit of 99,999 atoms (which is the upper limit of atoms available in one PDB file)
 */
UCLASS()
class MOLVIZ_API ABenchmarkGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ABenchmarkGameModeBase();
	TWeakObjectPtr<AProteinData> AddProtein();
	TWeakObjectPtr<AProteinRepresentation> AddProteinRep();
	TWeakObjectPtr<AProteinData> AddNewMolecule();
	void SetupNewMolecule();
	void ResetProteins();
	//method to create protein rep
	void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void RotateMolecule(float DeltaSeconds);


	bool IsFinished;
private:
	FPdbReader Reader;
	FSSReader SSReader;
	URepresentationFactory * RepFactory;
	TArray<TWeakObjectPtr<AProteinRepresentation>> ProteinReps;
	TArray<TWeakObjectPtr<AProteinData>> ProteinDatas;
	FString Path = "C:\\Users\\Govind\\Documents\\vmd-1.9.4a43\\proteins\\3b43.pdb";
	FTimerHandle NewProteinTimer;
	int32 AtomCount;
};
