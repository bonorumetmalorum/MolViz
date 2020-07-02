// Fill out your copyright notice in the Description page of Project Settings.


#include "AProteinData.h"

AProteinData::AProteinData()
{
}

AProteinData::~AProteinData()
{
}

void AProteinData::LoadComplete()
{
	LoadCompleteDelegate.Broadcast();
}

void AProteinData::CreateBonds()
{
	for(auto AtomA = Atoms.CreateIterator(); AtomA.GetIndex() < Atoms.Num(); ++AtomA)
	{
		for(auto AtomB = Atoms.CreateIterator(); AtomB.GetIndex() < Atoms.Num(); ++AtomB)
		{
			if (AtomA->Snum == AtomB->Snum)
				continue; //if we have the same atom, skip
			//if either one is a hydrogen do...
			if(AtomA->IsHydrogen() || AtomB->IsHydrogen())
			{ 
				auto InterAtomVec = AtomA->position - AtomB->position;
				auto SquaredLength = InterAtomVec.SizeSquared();
				if((0.16 <= SquaredLength) && (SquaredLength <= 1.44))
				{ //if they are within this squared distance, add a bond
					auto index = Bonds.Add(FBondData(AtomA.GetIndex(), AtomB.GetIndex(), InterAtomVec));
					Residues[AtomA->Resnum-1].bonds.Add(index);
					AtomA->Bonds.Add(&Atoms[AtomB.GetIndex()]);
				}
			}
			else
			{ //if they are not hydrogens, do...
				auto InterAtomVec = AtomA->position - AtomB->position;
				auto SquaredLength = InterAtomVec.SizeSquared();
				if ((0.16 <= SquaredLength) && (SquaredLength <= 3.61))
				{ //add a bond if the squared distance is in this range
					auto index = Bonds.Add(FBondData(AtomA.GetIndex(), AtomB.GetIndex(), InterAtomVec));
					Residues[AtomA->Resnum-1].bonds.Add(index);
					AtomA->Bonds.Add(&Atoms[AtomB.GetIndex()]);
				}
			}
		}
	}
}

void AProteinData::FindBackBone()
{
	for(auto ResIter = Residues.CreateIterator(); ResIter.GetIndex() < Residues.Num(); ++ResIter)
	{
		if (ResIter.GetIndex() == 0 || ResIter.GetIndex() == Residues.Num() - 1) //first residue
		{
			//find backbone atoms
			FAtomData * AtomCA = nullptr, * AtomN = nullptr, * AtomC = nullptr;
			for (auto AtomIter = ResIter->atoms.CreateIterator(); AtomIter.GetIndex() < ResIter->atoms.Num(); ++AtomIter)
			{
				FAtomData * Data = *AtomIter;
				if(Data->Name.Contains("CA"))
				{
					AtomCA = *AtomIter;
				}
				if (Data->Name.Contains("C"))
				{
					AtomC = *AtomIter;
				}
				if (Data->Name.Contains("N"))
				{
					AtomN = *AtomIter;
				}
			}
			if(AtomHasInterResidueBond(AtomC))
			{ // N terminus
				BackBone.Add(AtomN);
				BackBone.Add(AtomCA);
				BackBone.Add(AtomC);
			}
			else
			{// N Terminus
				BackBone.Add(AtomN);
				BackBone.Add(AtomCA);
				BackBone.Add(AtomC);
			}
		}
		else
		{
			//middle residues
			int NCount = 0;
			for(auto AtomIter = ResIter->atoms.CreateIterator(); AtomIter; ++AtomIter)
			{
				auto AtomNeighborIter = (*AtomIter)->Bonds.CreateIterator();
				while(AtomNeighborIter)
				{
					if(AtomHasInterResidueBond(*AtomNeighborIter))
					{
						NCount++;
					}
				}
				if(NCount == 2)
				{//this is part of the backbone
					AtomNeighborIter.Reset();
					for (; AtomNeighborIter; ++AtomNeighborIter)
					{
						if(AtomHasInterResidueBond(*AtomNeighborIter))
						{
							BackBone.Add(*AtomNeighborIter);
						}
					}
				}
				NCount = 0;
			}
		}

	}
}

void AProteinData::AddResidue(FString Resname, int32 Resnum)
{
	if(Resnum <= Residues.Num())
	{
		return;
	}
	Residues.Add(FResidue(Resname, Resnum));
}

void AProteinData::AddAtom(int32 Snum, uint8 Alt, FString Name, uint8 Chain, int32 Resnum, uint8 Insertion_residue_code, FVector position, float Occupancy, float TempFactor, FString Element)
{
	//check if the residue of this atom exists, if so add the atom to the atom array and get its index added to the residue
	if(Residues.Num() < Resnum) //we have not added this residue yet
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add atom %d, non-existant residue: %d"), Snum, Resnum);
		return;
	}
	//if the residue does not exist yet then create a new residue to add it to.
	int index = Atoms.Add(FAtomData(Snum, Alt, Name, Chain, Resnum, Insertion_residue_code, position, Occupancy, TempFactor, Element));
	Residues[Resnum-1].atoms.Add(&Atoms[index]);
}

void AProteinData::BeginPlay()
{
	Atoms.Reset();
	Residues.Reset();
}

bool AProteinData::AtomHasInterResidueBond(FAtomData * Atom)
{
	for(auto Iter = Atom->Bonds.CreateIterator(); Iter; ++Iter)
	{
		if ((*Iter)->Resnum != Atom->Resnum) return true;
	}
	return false;
}
