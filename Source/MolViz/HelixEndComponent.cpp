// Fill out your copyright notice in the Description page of Project Settings.


#include "HelixEndComponent.h"

#include "UObject/ConstructorHelpers.h"

UHelixEndComponent::UHelixEndComponent() : UBackBoneComponent()
{
	//set the static mesh of this part of the tube
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/HelixEnd.HelixEnd'"));
	UStaticMesh* Asset = Mesh.Object;
	SetForwardAxis(ESplineMeshAxis::Y);
	//SetSplineUpDir(FVector(0,0,1));
	USplineMeshComponent::SetStaticMesh(Asset);
	
}
