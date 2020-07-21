// Fill out your copyright notice in the Description page of Project Settings.


#include "FBackBoneSegmentData.h"

#include "FAtom.h"

FBackBoneSegmentData::FBackBoneSegmentData()
{
}

FBackBoneSegmentData::FBackBoneSegmentData(FAtomData* InN, FAtomData* InC, FAtomData* InO)
{
	this->N = InN;
	this->C = InC;
	this->O = InO;
}

FBackBoneSegmentData::~FBackBoneSegmentData()
{
}
