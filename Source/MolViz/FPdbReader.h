// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	void readStructure(FString filepath, AActor * protein) override;

private:
	LineType getLineType(const uint8 * line);
	void ParseTer(uint8* line, AProteinData* Cast);
	void ParseAtom(uint8* line, AProteinData * Protein);
};
