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
				ParseAtom(buffer);
				break;
			case Hetatm:
				break;
			case Model:
				break;
			case End:
				break;
			case Other:
				UE_LOG(LogTemp, Warning, TEXT("No support for: %s"),  *(BytesToString(buffer, 6)));
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("finished parsing file"));
}

LineType FPdbReader::getLineType(const uint8 * line)
{
	FString word = BytesToString(line, 6);
	if(word.Equals("HEADER", ESearchCase::Type::IgnoreCase))
	{
		return Header;
	}
	if (word.Equals("SEQRES", ESearchCase::Type::IgnoreCase))
	{
		return Seqres;
	}
	if (word.Equals("ATOM", ESearchCase::Type::IgnoreCase))
	{
		return Atom;
	}
	if (word.Equals("HETATM", ESearchCase::Type::IgnoreCase))
	{
		return Hetatm;
	}
	if (word.Equals("END", ESearchCase::Type::IgnoreCase))
	{
		return End;
	}
	return Other;
}

void FPdbReader::ParseAtom(uint8* line)
{
	//int32 Snum = -1;
	//uint8 Name[5] = { '\0' };
	//uint8 Alt = '\0';
	//uint8 Resname[4] = { '\0' };
	//uint8 Chain;
	//int32 Resnum = -1;
	//uint8 Insertion_residue_code;
	//float x, y, z;
	//float Occupancy, TempFactor;
	//uint8 SegID[5] = { '\0' }, Element[3] = { '\0' }, Charge[3] = { '\0' };

	FString type = BytesToString(line, 6); //0-6
	line += 6;
	FString serial = BytesToString(line, 4); //7 - 11
	line += 6;
	FString name = BytesToString(line, 3);
	line += 3;
	FString altLoc = BytesToString(line, 1);
	line += 1;
	FString resName = BytesToString(line, 2);
	line += 4;
	FString chainID = BytesToString(line, 1);
	line += 1;
	FString resSeq = BytesToString(line, 3);
	line += 3;
	FString iCode = BytesToString(line, 1);
	line += 4;
	FString X = BytesToString(line, 7);
	line += 7;
	FString Y = BytesToString(line, 7);
	line += 7;
	FString Z = BytesToString(line, 7);
	line += 7;
	FString occupancy = BytesToString(line, 5);
	line += 5;
	FString tempFactor = BytesToString(line, 5);
	line += 5;
	FString element = BytesToString(line, 3);
	line += 3;
	FString charge = BytesToString(line, 1);
	line += 1;

	
}
