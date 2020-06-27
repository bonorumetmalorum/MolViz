// Fill out your copyright notice in the Description page of Project Settings.


#include "FBondData.h"

FBondData::FBondData() :
	AtomA(-1),
	AtomB(-1)
{
}

FBondData::FBondData(int AtomA, int AtomB)
{
	this->AtomA = AtomA;
	this->AtomB = AtomB;
}

FBondData::~FBondData()
{
}
