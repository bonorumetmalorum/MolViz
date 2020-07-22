// Fill out your copyright notice in the Description page of Project Settings.


#include "BackBoneComponent.h"

#include "UObject/ConstructorHelpers.h"

UBackBoneComponent::UBackBoneComponent()
{
	//initialize the backbone variables and some settings for debugging the spline component
	Backbone.Init(nullptr, 4);
	bAllowSplineEditingPerInstance = true;
}

void UBackBoneComponent::SetStartingBackbone(FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom)
{
	this->Backbone[0] = StartAtom;
	this->Backbone[1] = ControlAtom;
	this->Backbone[2] = EndAtom;
	this->Backbone[3] = ControlAtom;

	//this is wrong, because this converts to bezier but we have a hermite curve...
	/*
	 *  CP1 = startatom + 2 / 3 * (controlatom - startatom)
	 *	CP2 = endatom + 2 / 3 * (controlatom - endatom)
	*/
	
	this->IsStartingBackBone = true;
	SetStartAndEnd(StartAtom->position, StartAtom->position - ControlAtom->position, EndAtom->position, FVector(1));

}

void UBackBoneComponent::SetBackbone(FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC)
{
	this->Backbone[0] = CurrentCA;
	this->Backbone[1] = CurrentC;
	this->Backbone[2] = NextCA;
	this->Backbone[3] = NextC;
	
#define SPLINE_FACTOR 2.0
	FVector StartTangentVec = CurrentC->position - CurrentCA->position;
	FVector EndTangentVec = NextC->position - NextCA->position;
	StartTangentVec.Normalize();
	EndTangentVec.Normalize();
	FVector Up = FVector::CrossProduct(StartTangentVec, EndTangentVec);
	Up.Normalize();
	this->SetSplineUpDir(Up);
	SetStartAndEnd(CurrentCA->position, (CurrentC->position - CurrentCA->position) * SPLINE_FACTOR /*C - CA*/, NextCA->position, (NextC->position - NextCA->position) * SPLINE_FACTOR /*C - CA*/);
}

FRotator UBackBoneComponent::MakeRotation(FAtomData* C1, FAtomData* C2, FAtomData* O)
{
	FVector Dir = C2->position - C1->position;
	Dir.Normalize();
	FVector OxDir = O->position - C1->position;
	OxDir.Normalize();
	SetSplineUpDir(FVector::CrossProduct(Dir, OxDir));
	return FRotationMatrix::MakeFromXY(Dir,OxDir).Rotator();
}

void UBackBoneComponent::UpdateBackBone()
{
	/*
	 * TODO atom positions have changed in this case so we recompute the control points and update the curve
	 */
}
