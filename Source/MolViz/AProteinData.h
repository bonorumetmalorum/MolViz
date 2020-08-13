// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAtom.h"
#include "FBackBoneSegmentData.h"
#include "FChainData.h"
#include "FBondData.h"
#include "FResidue.h"
#include "GameFramework/Info.h"
#include "AProteinData.generated.h"
//forward declarations
class AProteinRepresentation;

/**
 * Class that stores all information on a protein
 * tracks residues, hetresidues, bonds, chains and atoms.
 */
UCLASS()
class MOLVIZ_API AProteinData : public AInfo
{
	GENERATED_BODY()
public:
	AProteinData();
	~AProteinData();

	/*
	 * Creates the bonds between all loaded atoms on a distance based approach
	 */
	void CreateBonds();
	/*
	 * Finds all backbone atoms in the protein. assumes protein structure
	 */
	void FindBackBone();
	/*
	 * Finds a residue in a given chain
	 * @param ChainIndex the index of the chain internally = ChainID - 1
	 * @param Resnum the Residue number of the residue being searched for
	 * @param OrdinalResnum Residue number - 1
	 */
	FResidue* FindResidueInChain(uint8 ChainIndex, int32 Resnum, uint32 OrdinalResnum);
	/*
	 * adds a new residue
	 * @param Resname the residue name
	 * @param Resnum the residue number
	 */
	uint32 AddResidue(FString Resname, int32 Resnum);
	/*
	 * adds a new heterogeneous residue
	 * @param Resname the residue name
	 * @param Resnum the residue number
	 */
	uint32 AddHetResidue(FString Resname, int32 Resnum);
	/*
	 * add a new atom to the protein, adding it to the right residue and chain
	 * @param Snum the serial number of the atom
	 * @param Alt the alternative location of the atom
	 * @param Name the name of the atom
	 * @param Chain the chain the atom belongs to
	 * @param Resnum the residue number of the atom
	 * @param Insertion_residue_code the residue code of th atom
	 * @param position the x, y, z position of the atom
	 * @param Occupancy
	 * @param TempFactory
	 * @param Element the element type of the atom
	 */
	void AddAtom(int32 Snum, uint8 Alt, FString Name, uint8 Chain, int32 Resnum, uint8 Insertion_residue_code, 
					FVector position, float Occupancy, float TempFactor, FString Element);
	/*
	 * add a new heterogeneous atom to the protein, adding it to the right residue and chain
	 * @param Snum the serial number of the atom
	 * @param Alt the alternative location of the atom
	 * @param Name the name of the atom
	 * @param Chain the chain the atom belongs to
	 * @param Resnum the residue number of the atom
	 * @param Insertion_residue_code the residue code of th atom
	 * @param position the x, y, z position of the atom
	 * @param Occupancy
	 * @param TempFactory
	 * @param Element the element type of the atom
	 */
	void AddHetAtom(int32 Snum, uint8 Alt, FString Name, uint8 Chain, int32 Resnum, uint8 Insertion_residue_code,
	                FVector position, float Occupancy, float TempFactor, FString Element);
	TArray<FAtomData> Atoms;
	TArray<FResidue> Residues;
	TArray<FResidue> HetResidues;
	TArray<FBondData> Bonds;
	TArray<FChainData> Chains;
	TArray<FBackBoneSegmentData> BackBoneSegments; //make a list of back bone segments that contain, Current C, Current O, and Current N
	TWeakObjectPtr<AProteinRepresentation> Representation;
	FString FilePath;
	/*
	 * Finds the Center of Mass of the protein
	 */
	const FVector FindCOM();
	void BeginPlay() override;
private:
	bool AtomHasInterResidueBond(FAtomData & Atom);
};
