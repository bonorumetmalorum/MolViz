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
	//for all atoms
	for(auto AtomA = Atoms.CreateIterator(); AtomA; ++AtomA)
	{
		//for all atoms
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
	uint32 StartIndex = 0, EndIndex = 0;
	//for all chains
	for(auto ChainIter = Chains.CreateIterator(); ChainIter; ChainIter++) //for each chain
	{
		//for all offsets in this chain
		for(auto OffsetIter = ChainIter->ResidueOffsets.CreateConstIterator(); OffsetIter; OffsetIter++) //for each set of offsets
		{
			//for all residues between the offsets
			for(uint32 Residue = OffsetIter->Key; Residue <= OffsetIter->Value; Residue++) //for each residue between start and end offsets
			{
				int N = -1, C = -1;
				FBackBoneSegmentData BackBoneSegment;
				//for all atoms in the residues of the chain
				for (auto AtomIter = Residues[Residue].atoms.CreateIterator(); AtomIter; ++AtomIter)
				{
					int Data = *AtomIter;
					//match the element types
					if (Atoms[Data].Name.Equals("CA"))
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
				//only add the atom if it is a valid back bone segment
				if (BackBoneSegment.IsValid())
				{
					BackBoneSegment.ResType = Residues[Residue].SSResType;
					BackBoneSegments.Add(BackBoneSegment);
					EndIndex++;
				}
			}
		}
		ChainIter->StartBackBoneIndex = StartIndex;
		ChainIter->EndBackBoneIndex = EndIndex;
		StartIndex = EndIndex + 1;
	}
}

FResidue* AProteinData::FindResidueInChain(uint8 ChainIdentifier, int32 Resnum, uint32 OrdinalResNum)
{
	FChainData* Chain = nullptr;
	//if the chain identifier is empty return the first and only chain
	if(ChainIdentifier == '-')
	{
		Chain = &Chains[0];
	}
	//otherwise find the chain
	else
	{
		Chain = Chains.FindByKey(ChainIdentifier);
	}
	//if no chain was found return nullptr
	if(!Chain)
	{
		UE_LOG(LogTemp, Warning, TEXT("unkown chain %c"), ChainIdentifier);
		return nullptr;
	}
	//if a chain was found, iterate over the offsets
	for(auto OffsetsIter = Chain->ResidueOffsets.CreateConstIterator(); OffsetsIter; OffsetsIter++)
	{
		//if the ordinal res num is within the range of these offsets
		if((OrdinalResNum-1) <= (OffsetsIter->Value - OffsetsIter->Key))
		{
			FResidue* Residue = &Residues[OffsetsIter->Key + (OrdinalResNum-1)]; //get the residue by ordinal res num
			if(Residue->Resseq == Resnum)
			{ //if it is the residue we are looking for return
				return Residue;
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Reached end of chain and residue finding"));
	return nullptr;
}

uint32 AProteinData::AddResidue(FString Resname, int32 Resnum)
{
	//if we dont have any residues add one
	if(Residues.Num() == 0)
	{
		return Residues.Add(FResidue(Resname, Resnum));
	}
	//if we have residues but this one has not been added, add it
	if(Residues[Residues.Num() - 1].Resseq != Resnum)
	{
		return Residues.Add(FResidue(Resname, Resnum));
	}
	//return the most recently added residue
	return Residues.Num()-1;
}

uint32 AProteinData::AddHetResidue(FString Resname, int32 Resnum)
{
	//if we dont have any residues add one
	if (HetResidues.Num() == 0)
	{
		return HetResidues.Add(FResidue(Resname, Resnum));
	}
	//if we have residues but this one has not been added, add it
	if (HetResidues[HetResidues.Num() - 1].Resseq != Resnum)
	{
		return HetResidues.Add(FResidue(Resname, Resnum));
	}
	//return the most recently added residue
	return HetResidues.Num() - 1;
}

void AProteinData::AddAtom(int32 Snum, uint8 Alt, FString Name, uint8 Chain, int32 Resnum, uint8 Insertion_residue_code, FVector position, float Occupancy, float TempFactor, FString Element)
{
	Name.RemoveSpacesInline(); //remove any spaces in the name
	int index = Atoms.Add(FAtomData(Snum, Alt, Name, Chain, Resnum, Insertion_residue_code, position, Occupancy, TempFactor, Element));//add the atom and get its index
	if (Residues[Residues.Num() - 1].Resseq == Resnum) 
	{ //add the atom to the residue it belongs to
		Residues[Residues.Num() - 1].atoms.Add(index);
		Atoms[index].ResIndex = Residues.Num()-1;
	}
	else //residue does not exists
		UE_LOG(LogTemp, Warning, TEXT("Floating Atom, no residue found for sequence number %f"), Resnum);
}

void AProteinData::AddHetAtom(int32 Snum, uint8 Alt, FString Name, uint8 Chain, int32 Resnum, uint8 Insertion_residue_code, FVector position, float Occupancy, float TempFactor, FString Element)
{
	Name.RemoveSpacesInline();//remove any spaces in the name
	int index = Atoms.Add(FAtomData(Snum, Alt, Name, Chain, Resnum, Insertion_residue_code, position, Occupancy, TempFactor, Element));
	if (HetResidues[HetResidues.Num() - 1].Resseq == Resnum)
	{//add the atom to the residue it belongs to
		HetResidues[HetResidues.Num() - 1].atoms.Add(index);
		Atoms[index].ResIndex = HetResidues.Num() - 1;
	}
	else//residue does not exists
		UE_LOG(LogTemp, Warning, TEXT("Floating Atom, no residue found for sequence number %f"), Resnum);
}

void AProteinData::BeginPlay()
{
	//clear if there is anything here from a previous PIE session
	Atoms.Reset();
	Residues.Reset();
}

void AProteinData::SetRepresentation(const TWeakObjectPtr<AProteinRepresentation>& Rep)
{
	this->Representation = Rep;
}

TWeakObjectPtr<AProteinRepresentation> AProteinData::GetRepresentation()
{
	return Representation;
}

TArray<FBondData>& AProteinData::GetBonds()
{
	return Bonds;
}

FAtomData* AProteinData::GetAtom(const int Atom)
{
	return &Atoms[Atom];
}

TArray<FAtomData>& AProteinData::GetAtoms()
{
	return Atoms;
}

TArray<FChainData>& AProteinData::GetChains()
{
	return Chains;
}

TArray<FResidue>& AProteinData::GetResidues()
{
	return Residues;
}

void AProteinData::SetFilePath(const FString& CS)
{
	FilePath = CS;
}

TArray<FBackBoneSegmentData>& AProteinData::GetBackBoneSegments()
{
	return BackBoneSegments;
}

FBackBoneSegmentData* AProteinData::GetBackBoneSegment(uint32 BackBoneIndex)
{
	return &BackBoneSegments[BackBoneIndex];
}

TArray<FResidue>& AProteinData::GetHetResidues()
{
	return HetResidues;
}

FString AProteinData::GetFilePath()
{
	return FilePath;
}

bool AProteinData::AtomHasInterResidueBond(FAtomData & Atom)
{
	for(auto Iter = Atom.Neighbours.CreateIterator(); Iter; ++Iter)
	{
		if (Atoms[*Iter].Resnum != Atom.Resnum) return true; //index out of bounds error, possibly because the indeces stored here are not to the atoms??
	}
	return false;
}

const FVector AProteinData::FindCOM()
{
	FVector Sum(0); //current sum value
	for(auto AtomIter = Atoms.CreateConstIterator(); AtomIter; AtomIter++)
	{ //for all atoms add its position to the sum
		Sum += AtomIter->position;
	}
	//devide the sum by the number of atoms
	return Sum / Atoms.Num();
}
