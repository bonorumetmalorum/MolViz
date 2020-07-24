// Fill out your copyright notice in the Description page of Project Settings.


#include "FChainData.h"

FChainData::FChainData()
{
}

FChainData::FChainData(int32 InSerialNumber, FString InResname, uint8 InChainID, int32 InResSeq, uint8 InCodeForInsertionsOfResidues, int StartResIndex, int EndResIndex)
{
	SerialNumber = InSerialNumber;
	Resname = InResname;
	ChainID = InChainID;
	ResSeq = InResSeq;
	CodeForInsertionsOfResidues = InCodeForInsertionsOfResidues;
	StartIndex = StartResIndex;
	EndIndex = EndResIndex;
	ResidueOffsets.Add(TPair<uint32, uint32>(StartIndex, EndIndex));
}


FChainData::~FChainData()
{
}

bool FChainData::operator==(uint8 Index)
{
	return this->ChainID == Index;
}
