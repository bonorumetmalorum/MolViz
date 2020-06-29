// Fill out your copyright notice in the Description page of Project Settings.


#include "FBondData.h"

FBondData::FBondData() :
	AtomA(-1),
	AtomB(-1),
	Direction(0.f)
{
}

FBondData::FBondData(int AtomA, int AtomB, FVector Direction)
{
	this->AtomA = AtomA;
	this->AtomB = AtomB;
	this->Direction = Direction;
}

FBondData::~FBondData()
{
}
