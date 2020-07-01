// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Reader.h"

class AProteinData;

enum LineType
{
	Asg,
	Rem,
	Loc,
	Str,
	Chn,
	Seq,
	Other
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
	LineType GetLineType(const uint8* line);
	
};
