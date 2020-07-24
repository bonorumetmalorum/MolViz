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
					Residues[AtomA->ResIndex].bonds.Add(index);
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
					Residues[AtomA->ResIndex].bonds.Add(index);
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
		//if (ResIter.GetIndex() == 0 || ResIter.GetIndex() == Residues.Num() - 1) //first residue
		//{
			//find backbone atoms
			int N = -1, C = -1;
			FBackBoneSegmentData BackBoneSegment;
			for (auto AtomIter = ResIter->atoms.CreateIterator(); AtomIter.GetIndex() < ResIter->atoms.Num(); ++AtomIter)
			{
				int Data = *AtomIter;
				if(Atoms[Data].Name.Equals("CA"))
				{
					BackBoneSegment.CA = &Atoms[Data];
				}
				if (Atoms[Data].Name.Equals("C"))
				{
					BackBoneSegment.C = &Atoms[Data];
				}
				if (Atoms[Data].Name.Equals("N"))
				{
					BackBoneSegment.N = &Atoms[Data];
				}
				if (Atoms[Data].Name.Equals("O"))
				{
					BackBoneSegment.O = &Atoms[Data];
				}
			}
			if(BackBoneSegment.IsValid())
			{
				BackBoneSegment.ResType = ResIter->SSResType;
				BackBoneSegments.Add(BackBoneSegment);
			}
	}
}

FResidue* AProteinData::FindResidueInChain(uint8 ChainIdentifier, int32 Resnum, uint32 OrdinalResNum)
{
	FChainData* Chain = nullptr;
	if(ChainIdentifier == '-')
	{
		Chain = &Chains[0];
	}
	else
	{
		Chain = Chains.FindByKey(ChainIdentifier);
	}

	if(!Chain)
	{
		UE_LOG(LogTemp, Warning, TEXT("unkown chain %c"), ChainIdentifier);
		return nullptr;
	}
	
	for(auto OffsetsIter = Chain->ResidueOffsets.CreateConstIterator(); OffsetsIter; OffsetsIter++)
	{
		if((OrdinalResNum-1) <= (OffsetsIter->Value - OffsetsIter->Key))
		{
			FResidue* Residue = &Residues[OffsetsIter->Key + (OrdinalResNum-1)];
			if(Residue->Resseq == Resnum)
			{
				return Residue;
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Reached end of chain and residue finding"));
	return nullptr;
}

uint32 AProteinData::AddResidue(FString Resname, int32 Resnum)
{
	if(Residues.Num() == 0)
	{
		return Residues.Add(FResidue(Resname, Resnum));
	}
	if(Residues[Residues.Num() - 1].Resseq != Resnum)
	{
		return Residues.Add(FResidue(Resname, Resnum));
	}
	return Residues.Num()-1;
}

void AProteinData::AddAtom(int32 Snum, uint8 Alt, FString Name, uint8 Chain, int32 Resnum, uint8 Insertion_residue_code, FVector position, float Occupancy, float TempFactor, FString Element)
{
	//check if the residue of this atom exists, if so add the atom to the atom array and get its index added to the residue
	
	//if(Residues[Residues.Num()-1].Resseq < Resnum) //we have not added this residue yet
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Unable to add atom %d, non-existant residue: %d"), Snum, Resnum);
	//	return;
	//}
	//if the residue does not exist yet then create a new residue to add it to.
	Name.RemoveSpacesInline();
	int index = Atoms.Add(FAtomData(Snum, Alt, Name, Chain, Resnum, Insertion_residue_code, position, Occupancy, TempFactor, Element));
	if (Residues[Residues.Num() - 1].Resseq == Resnum)
	{
		Residues[Residues.Num() - 1].atoms.Add(index);
		Atoms[index].ResIndex = Residues.Num()-1;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Floating Atom, no residue found for sequence number %f"), Resnum);
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
