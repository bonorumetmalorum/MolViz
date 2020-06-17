// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Reader.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFilemanager.h"

enum LineType
{
	Header,
	Atom,
	Seqres,
	Model,
	Hetatm,
	Master,
	End,
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
	void read(FString filepath) override;

private:
	LineType getLineType(const uint8 * line);
};
