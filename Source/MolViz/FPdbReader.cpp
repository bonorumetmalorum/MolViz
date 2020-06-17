// Fill out your copyright notice in the Description page of Project Settings.


#include "FPdbReader.h"

FPdbReader::FPdbReader()
{
}

FPdbReader::~FPdbReader()
{
}

void FPdbReader::read(FString filepath)
{
	IPlatformFile & file = FPlatformFileManager::Get().GetPlatformFile();
	IFileHandle * fhandle = file.OpenRead(*filepath, false);
	uint8 buffer[600];
	while(ReadLine(fhandle,buffer,600))
	{
		LineType linetype = getLineType(buffer);
		switch(linetype)
		{
			case Header:
				break;
			case Seqres:
				break;
			case Atom:
				break;
			case Hetatm:
				break;
			case Model:
				break;
			case End:
				break;
			default:
				UE_LOG(LogTemp, Warning, TEXT("Unknown line type %s"),  *(BytesToString(buffer, 6)));
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("finished parsing file"));
}

LineType FPdbReader::getLineType(const uint8 * line)
{
	FString word = BytesToString(line, 6);
	if(word.Compare("HEADER", ESearchCase::Type::IgnoreCase))
	{
		return Header;
	}
	else if (word.Compare("SEQRES", ESearchCase::Type::IgnoreCase))
	{
		return Seqres;
	}
	else if (word.Compare("ATOM", ESearchCase::Type::IgnoreCase))
	{
		return Atom;
	}
	else if (word.Compare("HETATM", ESearchCase::Type::IgnoreCase))
	{
		return Hetatm;
	}
	else
	{
		return Other;
	}
	return End;
}
