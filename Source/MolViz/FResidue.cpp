// Fill out your copyright notice in the Description page of Project Settings.


#include "FResidue.h"

FResidue::FResidue(): Resseq(0)
{
}

FResidue::FResidue(const FString& Resname, int32 Resseq): Resseq(Resseq), Resname(Resname)
{
}

FResidue::~FResidue()
{
}
