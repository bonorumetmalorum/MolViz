// Fill out your copyright notice in the Description page of Project Settings.


#include "Tube.h"

#include "UObject/ConstructorHelpers.h"

UTube::UTube()
{
	//set the static mesh of this part of the tube
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Cylinder.Cylinder'"));
	UStaticMesh* Asset = Mesh.Object;
	SetForwardAxis(ESplineMeshAxis::Y); 
	USplineMeshComponent::SetStaticMesh(Asset);
	Backbone.Reserve(4);
	bAllowSplineEditingPerInstance = true;
}

void UTube::SetBackbone(FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom)
{
	this->Backbone[0] = StartAtom;
	this->Backbone[1] = ControlAtom;
	this->Backbone[2] = EndAtom;
	this->Backbone[3] = ControlAtom;

	//TODO compute correct control points
	SetStartAndEnd(StartAtom->position, ControlAtom->position, EndAtom->position, ControlAtom->position);
}

void UTube::SetBackbone(FAtomData* StartAtom, FAtomData* StartControlAtom, FAtomData* EndAtom, FAtomData * EndControlAtom)
{
	this->Backbone[0] = StartAtom;
	this->Backbone[1] = StartControlAtom;
	this->Backbone[2] = EndAtom;
	this->Backbone[3] = EndControlAtom;
	
	//TODO compute the correct control points
	SetStartAndEnd(StartAtom->position, StartControlAtom->position, EndAtom->position, EndControlAtom->position);
}

void UTube::UpdateBackBone()
{
	/*
	 * TODO atom positions have changed in this case so we recompute the control points and update the curve
	 */
}
