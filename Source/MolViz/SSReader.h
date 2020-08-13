// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Reader.h"
#include "StrideInterface.h"
//forward declaration
class AProteinData;
//secondary structure line type
enum SSLineType
{
	Asg,
	Rem,
	Loc,
	Str,
	Chn,
	Seq,
	NotSupported
};

//secondary structure types
enum SSType
{
	AHelix,
	BStrand,
	Coil
};

/**
 * secondary structure reader
 */
class MOLVIZ_API FSSReader : IReader
{
public:
	FSSReader();
	~FSSReader();
	/**
	 * parse structure type from output of STRIDE program
	 * @param Buffer the buffer containing the STRIDE information
	 * @param the protein data to load the ss information into
	 */
	void ParseStructureType(unsigned char Buffer[600], AProteinData * ProteinData);
	/**
	 * read the STRIDE output
	 * @param filepath to the pdb for stride processing
	 * @param Structure the protein data to load the SS information into
	 */
	void readStructure(FString filepath, AActor* Structure) override;

private:
	SSLineType GetLineType(const uint8* line);
	FStrideInterface Stride;
};
