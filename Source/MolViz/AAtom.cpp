// Fill out your copyright notice in the Description page of Project Settings.


#include "AAtom.h"

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

FAtomData::~FAtomData()
{
}
