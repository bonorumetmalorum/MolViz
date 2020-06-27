// Fill out your copyright notice in the Description page of Project Settings.


#include "FAtom.h"

FAtomData::FAtomData():
	Snum(0),
	Alt(0),
	Chain(0),
	Resnum(0),
	Insertion_residue_code(0),
	Occupancy(0),
	TempFactor(0),
	Element{}
{
	
}

FAtomData::FAtomData(int32 Snum, uint8 Alt, uint8 Chain, int32 Resnum, uint8 Insertion_residue_code, FVector position,
	float Occupancy, float TempFactor, FString Element) :
		Snum(Snum),
		Alt(Alt),
		Chain(Chain),
		Resnum(Resnum),
		Insertion_residue_code(Insertion_residue_code),
		position(position),
		Occupancy(Occupancy),
		TempFactor(TempFactor),
		Element(Element)
{
	
}

FAtomData::~FAtomData()
{
}
