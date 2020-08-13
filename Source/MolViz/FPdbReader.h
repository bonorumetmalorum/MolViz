// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FColorData.h"
#include "Reader.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFilemanager.h"

class AProteinData;
class AProtein;

enum LineType
{
	Header,
	Atom,
	Seqres,
	Model,
	Hetatm,
	Master,
	End,
	Ter,
	Other
};

/**
 * Pdb Reader for PDB file format
 */
class MOLVIZ_API FPdbReader : public IReader
{
public:
	FPdbReader();
	~FPdbReader();
	/*
	 * main routine to read the structure of a PDB into a protein
	 * @param filepath the file path to the pdb
	 * @param protein the protein to populate with the data read in from the pdb
	 */
	void readStructure(FString filepath, AActor * protein) override;
	/*
	 * convert an atom name to a atom element
	 * @param name atom name
	 * @return atom element type
	 */
	static FString NameToType(FString name);

private:
	LineType getLineType(const uint8 * line);
	void ParseTer(uint8* line, AProteinData* Cast);
	void ParseAtom(uint8* line, AProteinData * Protein);
	void ParseHetAtom(uint8* line, AProteinData* Protein);
	void ParseEnd(AProteinData * Protein);
	uint32 NewChainStartOffset = 0;
	uint32 NewChainEndOffset = 0;
};
