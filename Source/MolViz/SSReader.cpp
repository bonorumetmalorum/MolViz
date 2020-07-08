// Fill out your copyright notice in the Description page of Project Settings.


#include "SSReader.h"

#include "AProteinData.h"

FSSReader::FSSReader()
{
}

FSSReader::~FSSReader()
{
}

void FSSReader::ParseStructureType(unsigned char Buffer[100], AProteinData* ProteinData)
{
	//read in the residue id and store the structure type
	//maybe store, helix begin, helix and helix end
	//coil does not change at all, its just a cylinder
	//beta sheet needs beta and beta end for arrow head.
	FString Resnum = "";
	FString Chainnum = "";
	char SStype = ' ';

	int32 ResidueNumber = -1;
	int32 ChainNumber = -1;

	Resnum = BytesToString(Buffer + 5, 2);
	LexFromString(ResidueNumber, *Resnum);
	Chainnum = BytesToString(Buffer + 11, 3);
	LexFromString(ChainNumber, *Chainnum);
	SStype = Buffer[24];

	switch(SStype)
	{
		case 'E':
			ProteinData->Residues[ResidueNumber].SSResType = SSType::BStrand;
			break;

		case 'H':
			ProteinData->Residues[ResidueNumber].SSResType = SSType::AHelix;
			break;
		
		default:
			ProteinData->Residues[ResidueNumber].SSResType = SSType::Coil;
			break;
	}
}

/*
 *						 
 * Typical stride line //ASG  THR -    9    9    B        Bridge   -113.85    157.34      21.9      ~~~~ 80 characters in length
 */
void FSSReader::readStructure(FString filepath, AActor* Structure)
{
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();
	IFileHandle* fhandle = file.OpenRead(*filepath, false);
	uint8 buffer[100];
	while (ReadLine(fhandle, buffer, 100))
	{
		SSLineType linetype = GetLineType(buffer);
		switch (linetype)
		{
		case Asg:
			ParseStructureType(buffer, Cast<AProteinData>(Structure));
			break;
		case Rem:
			break;
		case Str:
			break;
		case Chn:
			break;
		case Loc:
			break;
		case Seq:
			break;
		case NotSupported:
			UE_LOG(LogTemp, Warning, TEXT("No support for: %s"), *(BytesToString(buffer, 3)));
		}
	}
}

SSLineType FSSReader::GetLineType(const uint8* line)
{
	FString word = BytesToString(line, 3);
	if (word.Contains("ASG", ESearchCase::Type::IgnoreCase))
	{
		return SSLineType::Asg;
	}
	if (word.Contains("REM", ESearchCase::Type::IgnoreCase))
	{
		return SSLineType::Rem;
	}
	if (word.Contains("LOC", ESearchCase::Type::IgnoreCase))
	{
		return SSLineType::Loc;
	}
	if (word.Contains("STR", ESearchCase::Type::IgnoreCase))
	{
		return SSLineType::Str;
	}
	if (word.Contains("CHN", ESearchCase::Type::IgnoreCase))
	{
		return SSLineType::Chn;
	}
	if (word.Contains("SEQ", ESearchCase::Type::IgnoreCase))
	{
		return SSLineType::Seq;
	}
	return SSLineType::NotSupported;
}
