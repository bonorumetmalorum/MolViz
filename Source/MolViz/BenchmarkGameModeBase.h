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
 * it will load a pdb
 * make copies of the pdb until we reach the upper limit of 99,999 atoms (which is the upper limit of atoms available in one PDB file)
 */
UCLASS()
class MOLVIZ_API ABenchmarkGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ABenchmarkGameModeBase();
	/*
	 * create a new protein and add it to the world
	 */
	TWeakObjectPtr<AProteinData> AddProtein();
	/*
	 * create a new protein representation and add it to the world
	 */
	TWeakObjectPtr<AProteinRepresentation> AddProteinRep();
	/*
	 * add a new molecule, sets up a protein data class and its representation in one go
	 */
	TWeakObjectPtr<AProteinData> AddNewMolecule();
	/*
	 * creates a new molecule and sets it up with the loaded content of the test pdb
	 * only adds up to a threshold of 10,000 atoms
	 */
	void SetupNewMolecule();
	/*
	 * Resets the level
	 */
	void ResetProteins();
	//method to create protein rep
	void BeginPlay() override;

	/*
	 * simple function to rotate the first protein added to the scene
	 */
	UFUNCTION(BlueprintCallable)
	void RotateMolecule(float DeltaSeconds);

	//to keep track if the test has completed or not
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
