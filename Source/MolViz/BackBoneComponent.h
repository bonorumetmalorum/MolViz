// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAtom.h"
#include "Components/SplineMeshComponent.h"
#include "BackBoneComponent.generated.h"

/**
 * we need to get the spline
 */
UCLASS(Abstract)
class MOLVIZ_API UBackBoneComponent : public USplineMeshComponent
{
	GENERATED_BODY()

public:

	UBackBoneComponent();
	
	void SetStartingBackbone(FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom);
	void SetBackbone(FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
	FRotator MakeRotation(FAtomData* C1, FAtomData* C2, FAtomData* O);
	void UpdateBackBone();

private:
	TArray<FAtomData*> Backbone;
	bool IsStartingBackBone = false;
};
