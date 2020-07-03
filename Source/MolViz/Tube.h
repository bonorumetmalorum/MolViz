// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAtom.h"
#include "Components/SplineMeshComponent.h"
#include "Tube.generated.h"

/**
 * we need to get the spline
 */
UCLASS()
class MOLVIZ_API UTube : public USplineMeshComponent
{
	GENERATED_BODY()

public:

	UTube();
	
	void SetBackbone(FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom);

	void SetBackbone(FAtomData* StartAtom, FAtomData* StartControlAtom, FAtomData* EndAtom, FAtomData* EndControlAtom);
	void UpdateBackBone();

private:
	TArray<FAtomData*> Backbone;
};
