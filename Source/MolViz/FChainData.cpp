// Fill out your copyright notice in the Description page of Project Settings.


#include "FChainData.h"

FChainData::FChainData()
{
}

FChainData::FChainData(int32 InSerialNumber, FString InResname, uint8 InChainID, int32 InResSeq, uint8 InCodeForInsertionsOfResidues, int StartAtomIndex, int EndAtomIndex)
{
	SerialNumber = InSerialNumber;
	Resname = InResname;
	ChainID = InChainID;
	ResSeq = InResSeq;
	CodeForInsertionsOfResidues = InCodeForInsertionsOfResidues;
	StartIndex = StartAtomIndex;
	EndIndex = EndAtomIndex;
}


FChainData::~FChainData()
{
}
