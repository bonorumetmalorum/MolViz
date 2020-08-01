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

void FPdbReader::ParseEnd(AProteinData * Protein)
{
	//if for some reason we have no chains, we must create one.
	if(Protein->Chains.Num() == 0)
	{
		Protein->Chains.Add(FChainData(Protein->Atoms.Last().Snum + 1, Protein->Residues.Last().Resname, Protein->Atoms.Last().Chain, Protein->Residues.Last().Resseq, -1, 0, Protein->Residues.Num() - 1));
	}
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
				ParseHetAtom(buffer, Cast<AProteinData>(Protein));
				break;
			case Model:
				break;
			case Ter:
				ParseTer(buffer, Cast<AProteinData>(Protein));
				break;
			case End:
				ParseEnd(Cast<AProteinData>(Protein));
				break;
			case Other:
				UE_LOG(LogTemp, Warning, TEXT("No support for: %s"),  *(BytesToString(buffer, 6)));
		}
	}
	ParseEnd(Cast<AProteinData>(Protein));
	Cast<AProteinData>(Protein)->FilePath = filepath;
	Cast<AProteinData>(Protein)->CreateBonds();
	//broadcast "load succeeded"
	UE_LOG(LogTemp, Warning, TEXT("finished parsing file"));
}

FString FPdbReader::NameToType(FString name)
{
	if (name[0] == 'H')
	{
		return "H";
	}
	if (name[0] == 'O')
	{
		return "O";

	}
	if (name[0] ==  'N')
	{
		return "N";

	}
	if (name[0] == 'C')
	{
		return "C";

	}
	if (name[0] == 'S')
	{
		return "S";

	}
	if (name[0] == 'P')
	{
		return "P";

	}
	if (name[0] == 'Z')
	{
		return "Z";

	}
	if (name.Contains("LPA", ESearchCase::IgnoreCase))
	{
		return "LPA";

	}
	if (name.Contains("LPB", ESearchCase::IgnoreCase))
	{
		return "LPB";

	}
	return "O";
}

LineType FPdbReader::getLineType(const uint8 * line)
{
	FString word = BytesToString(line, 6);
	word.RemoveSpacesInline();
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
	if(word.Equals("TER", ESearchCase::IgnoreCase))
	{
		return Ter;
	}
	if (word.Equals("END", ESearchCase::Type::IgnoreCase))
	{
		return End;
	}
	return Other;
}

void FPdbReader::ParseTer(uint8* line, AProteinData* Cast)
{
	int32 SerialNumber;
	FString Resname;
	uint8 ChainID;
	int32 ResSeq;
	uint8 CodeForInsertionsOfResidues;

	FString type = BytesToString(line, 3); //0 - 2
	line += 6;
	FString SNum = BytesToString(line, 5); //6 - 10
	line += 11;
	Resname = BytesToString(line, 3); //17-19
	line += 4;
	ChainID = *line; //21
	line += 1;
	FString RSNum = BytesToString(line, 4); //22 - 25
	line += 4;
	FString Cfir = BytesToString(line, 1); //26

	LexFromString(SerialNumber, *SNum);
	LexFromString(ResSeq, *RSNum);
	LexFromString(CodeForInsertionsOfResidues, *Cfir);

	//now we need to store this information in the protein ds
	//if this is the first chain, i.e. the list is previously empty, then it assumes 0 - current atom list length
	//if this is the next chain, then we must start at the previous chain end and stop and current atom list length
	if(Cast->Chains.Num() == 0)
	{
		Cast->Chains.Add(FChainData(SerialNumber, Resname, ChainID, ResSeq, CodeForInsertionsOfResidues, 0, NewChainEndOffset));
	}
	else
	{
		FChainData* Chain = Cast->Chains.FindByKey(ChainID);
		if (Chain)
		{
			Chain->ResidueOffsets.Add(TPair<uint32, uint32>(NewChainStartOffset, NewChainEndOffset));
		}
		else
		{
			Cast->Chains.Add(FChainData(SerialNumber, Resname, ChainID, ResSeq, CodeForInsertionsOfResidues, NewChainStartOffset, NewChainEndOffset));
		}
		
	}
	NewChainStartOffset = NewChainEndOffset+1;
	
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
	Chain = *line;
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
	LexFromString(Resnum, *resSeq);
	LexFromString(Insertion_residue_code, *iCode);
	LexFromString(x, *X);
	LexFromString(y, *Y);
	LexFromString(z, *Z);
	LexFromString(Occupancy, *occupancy);
	LexFromString(TempFactor, *tempFactor);
	name.RemoveSpacesInline();
	Element = NameToType(name);

	NewChainEndOffset = Protein->AddResidue(resName, Resnum);
	Protein->AddAtom(Snum, Alt, name, Chain, Resnum, Insertion_residue_code, FVector(x, y, z), Occupancy, TempFactor, Element);
}

void FPdbReader::ParseHetAtom(uint8* line, AProteinData* Protein)
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
	Chain = *line;
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
	LexFromString(Resnum, *resSeq);
	LexFromString(Insertion_residue_code, *iCode);
	LexFromString(x, *X);
	LexFromString(y, *Y);
	LexFromString(z, *Z);
	LexFromString(Occupancy, *occupancy);
	LexFromString(TempFactor, *tempFactor);
	name.RemoveSpacesInline();
	Element = NameToType(name);

	int ResNumber = Protein->AddHetResidue(resName, Resnum);
	Protein->AddHetAtom(Snum, Alt, name, Chain, Resnum, Insertion_residue_code, FVector(x, y, z), Occupancy, TempFactor, Element);
}
