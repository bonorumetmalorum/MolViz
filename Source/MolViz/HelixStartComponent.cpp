// Fill out your copyright notice in the Description page of Project Settings.


#include "HelixStartComponent.h"

#include "UObject/ConstructorHelpers.h"

UHelixStartComponent::UHelixStartComponent() : UBackBoneComponent()
{
	//set the static mesh of this part of the tube
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/HelixEnd.HelixEnd'"));
	UStaticMesh* Asset = Mesh.Object;
	SetForwardAxis(ESplineMeshAxis::Y);
	//SetSplineUpDir(FVector(0,0,1));
	USplineMeshComponent::SetStaticMesh(Asset);
	SetCustomPrimitiveDataVector4(0, FVector4(1, 0, 0, 1));
}
