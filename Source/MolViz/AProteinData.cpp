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
	for(auto AtomA = Atoms.CreateConstIterator(); AtomA.GetIndex() < Atoms.Num(); ++AtomA)
	{
		for(auto AtomB = Atoms.CreateConstIterator(); AtomB.GetIndex() < Atoms.Num(); ++AtomB)
		{
			if (AtomA->Snum == AtomB->Snum)
				continue; //if we have the same atom, skip
			//if either one is a hydrogen do...
			if(AtomA->IsHydrogen() || AtomB->IsHydrogen())
			{ 
				auto InterAtomVec = AtomA->position - AtomB->position;
				auto SquaredLength = InterAtomVec.SizeSquared();
				if(0.16 <= SquaredLength <= 1.44)
				{ //if they are within this squared distance, add a bond
					Bonds.Add(FBondData(AtomA.GetIndex(), AtomB.GetIndex()));
				}
			}
			else
			{ //if they are not hydrogens, do...
				auto InterAtomVec = AtomA->position - AtomB->position;
				auto SquaredLength = InterAtomVec.SizeSquared();
				if (0.16 <= SquaredLength <= 3.61)
				{ //add a bond if the squared distance is in this range
					Bonds.Add(FBondData(AtomA.GetIndex(), AtomB.GetIndex()));
				}
			}
		}
	}
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
