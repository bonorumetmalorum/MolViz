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

class AProteinRepresentation;
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
	void FindBackBone();
	FResidue* FindResidueInChain(uint8 ChainIndex, int32 Resnum, uint32 OrdinalResnum);
	uint32 AddResidue(FString Resname, int32 Resnum);
	void AddAtom(int32 Snum, uint8 Alt, FString Name, uint8 Chain, int32 Resnum, uint8 Insertion_residue_code, FVector position, float Occupancy, float TempFactor, FString Element);
	TArray<FAtomData> Atoms;
	TArray<FResidue> Residues;
	TArray<FBondData> Bonds;
	TArray<FChainData> Chains;
	//TArray<FAtomData *> BackBone;
	TArray<FBackBoneSegmentData> BackBoneSegments; //make a list of back bone segments that contain, Current C, Current O, and Current N
	TWeakObjectPtr<AProteinRepresentation> Representation;
	FString FilePath;
	const FVector FindCOM();
	void BeginPlay() override;
private:
	bool AtomHasInterResidueBond(FAtomData & Atom);
	bool AtomHasInterResidueBond(FAtomData& Atom, int & Bonds);
};
