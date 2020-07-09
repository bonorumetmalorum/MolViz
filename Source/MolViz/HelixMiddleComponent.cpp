// Fill out your copyright notice in the Description page of Project Settings.


#include "HelixMiddleComponent.h"

#include "UObject/ConstructorHelpers.h"

UHelixMiddleComponent::UHelixMiddleComponent() : UBackBoneComponent()
{
	//set the static mesh of this part of the tube
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/HelixMiddle.HelixMiddle'"));
	UStaticMesh* Asset = Mesh.Object;
	SetForwardAxis(ESplineMeshAxis::Y);
	//SetSplineUpDir(FVector(0,0,1));
	USplineMeshComponent::SetStaticMesh(Asset);
}
