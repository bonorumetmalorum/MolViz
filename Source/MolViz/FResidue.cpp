// Fill out your copyright notice in the Description page of Project Settings.


#include "FResidue.h"

FResidue::FResidue(): Resseq(0)
{
}

FResidue::FResidue(const FString& Resname, int32 Resseq): Resname(Resname), Resseq(Resseq)
{
}

FResidue::~FResidue()
{
}

bool FResidue::operator==(int32 key)
{
	return this->Resseq == key;
}
