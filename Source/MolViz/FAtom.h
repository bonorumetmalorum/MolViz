// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAtom.generated.h"

/**
 * Represents 1 atom and all of its associated data
 */
USTRUCT(BlueprintType)
struct FAtomData
{
	GENERATED_BODY()

	FAtomData();
	FAtomData(int32 Snum, uint8 Alt, FString Name, uint8 Chain, int32 Resnum,	uint8 Insertion_residue_code, FVector position, float Occupancy, float TempFactor, FString Element);
	~FAtomData();
	bool IsHydrogen() const;
	//uint8_t nameindex;              ///< atom name string index
	//uint8_t typeindex;              ///< atom type string index
	//uint32_t uniq_resid;               ///< unique resid, since there can be dups
	//uint32_t bondTo[12L];     ///< list of atoms to which this atom is bonded - Max is 12
	//signed char bonds;            ///< how many bonds this atom has
	//signed char atomicnumber;     ///< element atomic number
	//signed char altlocindex;      ///< alternate location identifier index
	//char insertionstr[2];         ///< for insertion codes (padded to 2 chars)

	//// items which could potentially be moved into other data structures 
	//// to save memory, but are presently kept here for extra simplicity or speed
	//uint8_t chainindex;             ///< chain identifier
	//uint8_t segnameindex;           ///< atom segment name string index
	//uint32_t resid;                    ///< resid from original file
	//uint8_t resnameindex;           ///< atom residue name string index

	//// ATOMNORMAL, ATOMPROTEINBACK, ATOMNUCLEICBACK, ATOMHYDROGEN
	//// XXX this should be converted to an unsigned bit-field to save memory
	//signed char atomType;         ///< is this atom part of the backbone?

	///// used to tell me if this atom is part of some larger complete structure
	//// RESNOTHING, RESPROTEIN, RESNUCLEIC, RESWATERS
	//// XXX this should be converted to an unsigned bit-field to save memory
	//signed char residueType;      ///< is this part of a larger component?
	//							  ///< for instance, is this CG atom in an 
	//							  ///< amino acid of some sort?
	//
	int32 Snum;
	uint8 Alt;
	FString Name;
	uint8 Chain;
	int32 Resnum;
	uint8 Insertion_residue_code;
	FVector position;
	float Occupancy;
	float TempFactor;
	FString Element;
	TArray<int> Bonds;
};
