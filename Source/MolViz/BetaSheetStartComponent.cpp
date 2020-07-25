// Fill out your copyright notice in the Description page of Project Settings.


#include "BetaSheetStartComponent.h"

#include "UObject/ConstructorHelpers.h"

UBetaSheetStartComponent::UBetaSheetStartComponent() : UBackBoneComponent()
{
	//set the static mesh of this part of the tube
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Sheet.Sheet'"));
	UStaticMesh* Asset = Mesh.Object;
	SetForwardAxis(ESplineMeshAxis::Y);
	//SetSplineUpDir(FVector(0,0,1));
	USplineMeshComponent::SetStaticMesh(Asset);
}
