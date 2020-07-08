// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Reader.h"

class AProteinData;

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

enum SSType
{
	AHelix,
	BStrand,
	Coil
};

/**
 * 
 */
class MOLVIZ_API FSSReader : IReader
{
public:
	FSSReader();
	~FSSReader();

	void ParseStructureType(unsigned char Buffer[600], AProteinData * ProteinData);
	void readStructure(FString filepath, AActor* Structure) override;

private:
	SSLineType GetLineType(const uint8* line);
	
};
