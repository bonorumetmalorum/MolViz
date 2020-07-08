// Fill out your copyright notice in the Description page of Project Settings.


#include "FPdbReader.h"

#include "AProteinData.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

FPdbReader::FPdbReader()
{
}

FPdbReader::~FPdbReader()
{
}

void FPdbReader::readStructure(FString filepath, AActor * Protein)
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
				ParseAtom(buffer, Cast<AProteinData>(Protein));
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
	Cast<AProteinData>(Protein)->CreateBonds();
	
	//broadcast "load succeeded"
	Cast<AProteinData>(Protein)->LoadComplete();
	UE_LOG(LogTemp, Warning, TEXT("finished parsing file"));
}

LineType FPdbReader::getLineType(const uint8 * line)
{
	FString word = BytesToString(line, 6);
	if(word.Contains("HEADER", ESearchCase::Type::IgnoreCase))
	{
		return Header;
	}
	if (word.Contains("SEQRES", ESearchCase::Type::IgnoreCase))
	{
		return Seqres;
	}
	if (word.Contains("ATOM", ESearchCase::Type::IgnoreCase))
	{
		return Atom;
	}
	if (word.Contains("HETATM", ESearchCase::Type::IgnoreCase))
	{
		return Hetatm;
	}
	if (word.Contains("END", ESearchCase::Type::IgnoreCase))
	{
		return End;
	}
	return Other;
}

void FPdbReader::ParseAtom(uint8* line, AProteinData * Protein)
{
	int32 Snum = -1;
	uint8 Alt = '\0';
	FString Resname = "";
	uint8 Chain;
	int32 Resnum = -1;
	uint8 Insertion_residue_code;
	float x, y, z;
	float Occupancy, TempFactor;
	//uint8 Charge[3] = { '\0' };

	FString type = BytesToString(line, 6); //0-5
	line += 6; //6
	FString serial = BytesToString(line, 5); //6 - 10
	line += 6; //12
	FString name = BytesToString(line, 5); //12-15
	line += 4; //16
	FString altLoc = BytesToString(line, 1); //16
	line += 1; //17
	FString resName = BytesToString(line, 3); //17-19
	line += 4; //21
	FString chainID = BytesToString(line, 1); //21
	line += 1; //22
	FString resSeq = BytesToString(line, 4); //22-25 - issue with this one
	line += 4; //26
	FString iCode = BytesToString(line, 1); //26
	line += 4; //30
	FString X = BytesToString(line, 8); //30-37
	line += 8; //38
	FString Y = BytesToString(line, 8); //38-45
	line += 8; //46
	FString Z = BytesToString(line, 8); //46-53
	line += 8; //54
	FString occupancy = BytesToString(line, 6); //54-59
	line += 6; //60
	FString tempFactor = BytesToString(line, 5); //60-65
	line += 16; //76
	FString Element = BytesToString(line, 2); //76-77
	line += 2; //78
	//FString charge = BytesToString(line, 2); //78-79
	//line += 2;

	LexFromString(Snum, *serial);
	LexFromString(Alt, *altLoc);
	LexFromString(Chain, *chainID);
	LexFromString(Resnum, *resSeq);
	LexFromString(Insertion_residue_code, *iCode);
	LexFromString(x, *X);
	LexFromString(y, *Y);
	LexFromString(z, *Z);
	LexFromString(Occupancy, *occupancy);
	LexFromString(TempFactor, *tempFactor);

	//DrawDebugSphere(GEngine->GetWorldFromContextObject(GEngine->GameViewport, EGetWorldErrorMode::ReturnNull) , FVector(x*10, y*10, z*10), 10.0f, 10, FColor::Red, true, 100, 0, 2.f);
	Protein->AddResidue(resName, Resnum);
	Protein->AddAtom(Snum, Alt, name, Chain, Resnum, Insertion_residue_code, FVector(x, y, z), Occupancy, TempFactor, Element);
}
