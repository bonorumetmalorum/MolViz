// Fill out your copyright notice in the Description page of Project Settings.


#include "AProteinData.h"

AProteinData::AProteinData()
{
}

AProteinData::~AProteinData()
{
}

void AProteinData::CreateBonds()
{
}

void AProteinData::AddAtom(int32 Snum, uint8 Alt, uint8 Chain, int32 Resnum, uint8 Insertion_residue_code, FVector position, float Occupancy, float TempFactor, FString Element)
{
	Atoms.Add(FAtomData(Snum, Alt, Chain, Resnum, Insertion_residue_code, position, Occupancy, TempFactor, Element));
}

void AProteinData::BeginPlay()
{
	Atoms.Reset();
	Residues.Reset();
}
