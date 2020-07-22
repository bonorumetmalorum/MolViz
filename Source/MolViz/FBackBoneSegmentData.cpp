// Fill out your copyright notice in the Description page of Project Settings.


#include "FBackBoneSegmentData.h"

#include "FAtom.h"

FBackBoneSegmentData::FBackBoneSegmentData()
{
	this->N = nullptr;
	this->C = nullptr;
	this->O = nullptr;
	this->CA = nullptr;
}

FBackBoneSegmentData::FBackBoneSegmentData(FAtomData* InN, FAtomData* InC, FAtomData *InCA, FAtomData* InO, SSType InResType)
{
	this->N = InN;
	this->C = InC;
	this->O = InO;
	this->CA = InCA;
	this->ResType = InResType;
}

FBackBoneSegmentData::~FBackBoneSegmentData()
{
}

bool FBackBoneSegmentData::IsValid()
{
	return N && C && CA && O;
}
