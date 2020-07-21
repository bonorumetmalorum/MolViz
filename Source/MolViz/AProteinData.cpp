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
	for(auto AtomA = Atoms.CreateIterator(); AtomA; ++AtomA)
	{
		for(auto AtomB = Atoms.CreateIterator(); AtomB; ++AtomB)
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
					AtomA->Neighbours.Add(AtomB.GetIndex());
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
					AtomA->Neighbours.Add(AtomB.GetIndex());
				}
			}
		}
	}
}

void AProteinData::FindBackBone()
{
	for(auto ResIter = Residues.CreateIterator(); ResIter.GetIndex() < Residues.Num(); ResIter++)
	{
		if (ResIter.GetIndex() == 0 || ResIter.GetIndex() == Residues.Num() - 1) //first residue
		{
			//find backbone atoms
			int N = -1, C = -1;
			FAtomData * AtomCA = nullptr, * AtomN = nullptr, * AtomC = nullptr, *AtomO = nullptr;
			for (auto AtomIter = ResIter->atoms.CreateIterator(); AtomIter.GetIndex() < ResIter->atoms.Num(); ++AtomIter)
			{
				int Data = *AtomIter;
				if(Atoms[Data].Name.Equals("CA"))
				{
					AtomCA = &Atoms[Data];
				}
				if (Atoms[Data].Name.Equals("C"))
				{
					AtomC = &Atoms[Data];
				}
				if (Atoms[Data].Name.Equals("N"))
				{
					AtomN = &Atoms[Data];
				}
				if (Atoms[Data].Name.Equals("O"))
				{
					AtomO = &Atoms[Data];
				}
			}
			if(AtomC && AtomHasInterResidueBond(*AtomC, N))
			{ // N terminus
				//BackBone.Add(AtomN); // because we have an n terminus, N is part of another residue which is bonded to the C in this residue, we need to add it otherwise N is null :(
				BackBoneSegments.Add(AtomCA);
				BackBone.Add(&Atoms[N]);
				BackBone.Add(AtomC);
			}
			else if(AtomN && AtomHasInterResidueBond(*AtomN, C))
			{// N Terminus
				BackBone.Add(AtomN); 
				BackBone.Add(&Atoms[C]); // like wise the C in this case is null because it is in another residue, we need to find it and add it 
				BackBone.Add(AtomCA);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("no carboxyl / amine group detected"));
			}
		}
		else
		{
			//middle residues
			int NCount = 0;
			TArray<FAtomData*> Neighbors; //TODO find another way to do this maybe??
			for(auto AtomIter = ResIter->atoms.CreateIterator(); AtomIter; ++AtomIter)
			{
				FAtomData & AtomData = Atoms[*AtomIter];
				//auto AtomNeighborIter = AtomData->Neighbours.CreateIterator();
				for (int j = 0; j < AtomData.Neighbours.Num(); j++)
				{
					if (AtomHasInterResidueBond(Atoms[AtomData.Neighbours[j]]))
					{
						Neighbors.Add(&(Atoms[AtomData.Neighbours[j]]));
						NCount++;
					}
				}
				if(NCount == 2)
				{//this is part of the backbone
					BackBone.Add(&Atoms[*AtomIter]);
					BackBone.Add(Neighbors[0]);
					BackBone.Add(Neighbors[1]);
				}
				NCount = 0;
				Neighbors.Reset();
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
	Name.RemoveSpacesInline();
	int index = Atoms.Add(FAtomData(Snum, Alt, Name, Chain, Resnum, Insertion_residue_code, position, Occupancy, TempFactor, Element));
	Residues[Resnum-1].atoms.Add(index);
}

void AProteinData::BeginPlay()
{
	Atoms.Reset();
	Residues.Reset();
}

bool AProteinData::AtomHasInterResidueBond(FAtomData & Atom)
{
	for(auto Iter = Atom.Neighbours.CreateIterator(); Iter; ++Iter)
	{
		if (Atoms[*Iter].Resnum != Atom.Resnum) return true; //index out of bounds error, possibly because the indeces stored here are not to the atoms??
	}
	return false;
}

bool AProteinData::AtomHasInterResidueBond(FAtomData& Atom, int & OutAtom){
	for (auto Iter = Atom.Neighbours.CreateIterator(); Iter; ++Iter)
	{
		if (Atoms[*Iter].Resnum != Atom.Resnum)
		{
			OutAtom = *Iter;
			return true;
		}
	}
	OutAtom = -1;
	return false;
}

const FVector AProteinData::FindCOM()
{
	FVector Sum(0);
	for(auto AtomIter = Atoms.CreateConstIterator(); AtomIter; AtomIter++)
	{
		Sum += AtomIter->position;
	}
	return Sum / Atoms.Num();
}
