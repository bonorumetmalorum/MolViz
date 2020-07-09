// Fill out your copyright notice in the Description page of Project Settings.


#include "BetaSheetEndComponent.h"

#include "UObject/ConstructorHelpers.h"

UBetaSheetEndComponent::UBetaSheetEndComponent() : UBackBoneComponent()
{
	//set the static mesh of this part of the tube
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/SheetEnd.SheetEnd'"));
	UStaticMesh* Asset = Mesh.Object;
	SetForwardAxis(ESplineMeshAxis::Y);
	//SetSplineUpDir(FVector(0,0,1));
	USplineMeshComponent::SetStaticMesh(Asset);
}
