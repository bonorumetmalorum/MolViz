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

	int32 ResidueNumber = -1;
	int32 ChainNumber = -1;
	uint8 ChainIdentifier = Buffer[9];

	Resnum = BytesToString(Buffer + 11, 4);
	LexFromString(ResidueNumber, *Resnum);
	Chainnum = BytesToString(Buffer + 16, 4);
	
	LexFromString(ChainNumber, *Chainnum);
	uint8 SStype = Buffer[24];
	
	FResidue* Res = ProteinData->FindResidueInChain(ChainIdentifier, ResidueNumber, ChainNumber);
	switch(SStype)
	{
		case 'E':
			Res->SSResType = SSType::BStrand;
			//ProteinData->Residues[ResidueNumber-1].SSResType = SSType::BStrand;
			break;

		case 'H':
			Res->SSResType = SSType::AHelix;
			//ProteinData->Residues[ResidueNumber-1].SSResType = SSType::AHelix;
			break;
		
		default:
			Res->SSResType = SSType::Coil;
			//ProteinData->Residues[ResidueNumber-1].SSResType = SSType::Coil;
			break;
	}
	UE_LOG(LogTemp, Warning, TEXT("Reached end of SS parsing structure type"));
}

/*
 *						 
 * Typical stride line //ASG  THR -    9    9    B        Bridge   -113.85    157.34      21.9      ~~~~ 80 characters in length
 */
void FSSReader::readStructure(FString filepath, AActor* Structure)
{
	FString SSInfo = Stride.RunStrideCommand(filepath);
	uint8 buffer[100];
	SIZE_T offset = 0;
	while (ReadLine(SSInfo, buffer, offset, 100))
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
		UE_LOG(LogTemp, Warning, TEXT("Parsing SS file"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Reached end of SS parsing"));
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
