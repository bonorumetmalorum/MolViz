// Fill out your copyright notice in the Description page of Project Settings.


#include "BackBoneComponent.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"

UBackBoneComponent::UBackBoneComponent()
{
	//initialize the backbone variables and some settings for debugging the spline component
	Backbone.Init(nullptr, 4);
	bAllowSplineEditingPerInstance = true;
}

void UBackBoneComponent::SetStartingBackbone(FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom)
{
	//the elements of this backbone segment
	this->Backbone[0] = StartAtom;
	this->Backbone[1] = ControlAtom;
	this->Backbone[2] = EndAtom;
	this->Backbone[3] = ControlAtom;

	//if this is the starting backbone
	this->IsStartingBackBone = true;
	//create the underlying spline and mesh around it
	SetStartAndEnd(StartAtom->position, StartAtom->position - ControlAtom->position, EndAtom->position, FVector(1));

}

void UBackBoneComponent::SetBackbone(FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC)
{
	//the atoms that make this part of the backbone
	this->Backbone[0] = CurrentCA;
	this->Backbone[1] = CurrentC;
	this->Backbone[2] = NextCA;
	this->Backbone[3] = NextC;
//spline factor determines how curvy the backbone should be	
#define SPLINE_FACTOR 2.0
	//compute the tangent vector for the starting position
	FVector StartTangentVec = CurrentC->position - CurrentCA->position;
	//compute the tangent vector for the ending position
	FVector EndTangentVec = NextC->position - NextCA->position;
	//normalize both of these so we can scale as needed
	StartTangentVec.Normalize();
	EndTangentVec.Normalize();
	//create an up vector so we do not suffer from gimbal lock as the spline uses euler angles to rotate end and start
	FVector Up = FVector::CrossProduct(StartTangentVec, EndTangentVec);
	Up.Normalize(); //normalize it
	this->SetSplineUpDir(Up);
	//create the underlying spline and mesh around it
	SetStartAndEnd(CurrentCA->position, (CurrentC->position - CurrentCA->position) * SPLINE_FACTOR /*C - CA*/, NextCA->position, (NextC->position - NextCA->position) * SPLINE_FACTOR /*C - CA*/);
}

FMatrix UBackBoneComponent::MakeRotation(FAtomData* C1, FAtomData* C2, FAtomData* O)
{
	//the direction from the start to the end position
	FVector Dir = C2->position - C1->position;
	Dir.Normalize();
	//direction from the start to the oxygen
	FVector OxDir = O->position - C1->position;
	OxDir.Normalize();
	//debug routines to visuliase the axes
	/*DrawDebugLine(this->GetWorld(), C1->position, C2->position, FColor::Emerald, true);
	DrawDebugLine(this->GetWorld(), C1->position, O->position, FColor::Red, true);
	DrawDebugLine(this->GetWorld(), C1->position, FVector::CrossProduct(C1->position, O->position), FColor::Blue, true);*/
	//SetSplineUpDir(FVector::CrossProduct(Dir, OxDir));
	//make the rotation matrix from the two directions just calculated
	return FRotationMatrix::MakeFromXY(Dir,OxDir);
}

void UBackBoneComponent::UpdateBackBone()
{
	/*
	 * TODO
	 */
}
