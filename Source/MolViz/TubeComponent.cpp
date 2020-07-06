// Fill out your copyright notice in the Description page of Project Settings.


#include "TubeComponent.h"

#include "UObject/ConstructorHelpers.h"

UTubeComponent::UTubeComponent()
{
	//set the static mesh of this part of the tube
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Cylinder.Cylinder'"));
	UStaticMesh* Asset = Mesh.Object;
	SetForwardAxis(ESplineMeshAxis::Y); 
	USplineMeshComponent::SetStaticMesh(Asset);
	Backbone.Init(nullptr, 4);
	bAllowSplineEditingPerInstance = true;
}

void UTubeComponent::SetStartingBackbone(FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom)
{
	this->Backbone[0] = StartAtom;
	this->Backbone[1] = ControlAtom;
	this->Backbone[2] = EndAtom;
	this->Backbone[3] = ControlAtom;


	/*
	 *  CP1 = startatom + 2 / 3 * (controlatom - startatom)
	 *	CP2 = endatom + 2 / 3 * (controlatom - endatom)
	*/

	#define TWOBYTHREE 0.6666666666666667
	
	this->IsStartingBackBone = true;
	//TODO compute correct control points
	SetStartAndEnd(StartAtom->position, StartAtom->position + (TWOBYTHREE * (ControlAtom->position - StartAtom->position)), EndAtom->position, EndAtom->position + (TWOBYTHREE * (ControlAtom->position - EndAtom->position)));
}

void UTubeComponent::SetBackbone(FAtomData* PreviousResLastAtom, FAtomData* PreviousResControlAtom, FAtomData* CurrentResControlAtom, FAtomData * CurrentResEndAtom)
{
	this->Backbone[0] = PreviousResLastAtom;
	this->Backbone[1] = PreviousResControlAtom;
	this->Backbone[2] = CurrentResControlAtom;
	this->Backbone[3] = CurrentResEndAtom;
	
	//TODO compute the correct control points
	SetStartAndEnd(PreviousResLastAtom->position, PreviousResLastAtom->position + (PreviousResLastAtom->position - PreviousResControlAtom->position), 
		CurrentResEndAtom->position, CurrentResControlAtom->position);
}

void UTubeComponent::UpdateBackBone()
{
	/*
	 * TODO atom positions have changed in this case so we recompute the control points and update the curve
	 */
}
