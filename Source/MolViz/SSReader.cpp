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
		LineType linetype = GetLineType(buffer);
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
		case Other:
			UE_LOG(LogTemp, Warning, TEXT("No support for: %s"), *(BytesToString(buffer, 3)));
		}
	}
}

LineType FSSReader::GetLineType(const uint8* line)
{
	FString word = BytesToString(line, 3);
	if (word.Contains("ASG", ESearchCase::Type::IgnoreCase))
	{
		return Asg;
	}
	if (word.Contains("REM", ESearchCase::Type::IgnoreCase))
	{
		return Rem;
	}
	if (word.Contains("LOC", ESearchCase::Type::IgnoreCase))
	{
		return Loc;
	}
	if (word.Contains("STR", ESearchCase::Type::IgnoreCase))
	{
		return Str;
	}
	if (word.Contains("CHN", ESearchCase::Type::IgnoreCase))
	{
		return Chn;
	}
	if (word.Contains("SEQ", ESearchCase::Type::IgnoreCase))
	{
		return Seq;
	}
	return Other;
}
