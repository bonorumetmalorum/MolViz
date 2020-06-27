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

void AProteinData::AddAtom(float X, float Y, float Z)
{
	Atoms.Add(FAtomData());
	
}

void AProteinData::BeginPlay()
{
	Atoms.Reset();
	Residues.Reset();
}
