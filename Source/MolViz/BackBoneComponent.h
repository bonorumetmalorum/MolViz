// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAtom.h"
#include "Components/SplineMeshComponent.h"
#include "BackBoneComponent.generated.h"

/**
 * Abstract class to be inherited from representation elements that use backbone atoms
 */
UCLASS(Abstract)
class MOLVIZ_API UBackBoneComponent : public USplineMeshComponent
{
	GENERATED_BODY()

public:

	UBackBoneComponent();
	/*
	 * set the first backbone segment
	 * @Param StartAtom starting atom for this segment
	 * @Param ControlAtom control atom for this segment
	 * @Param EndAtom end atom for this segment
	 */
	void SetStartingBackbone(FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom);
	/*
	 * set the middle and end backbone segments
	 * @param CurrentCA current alpha carbon
	 * @param CurrentC current carbon
	 * @param NextCA next backbone segment CA
	 * @param NextC next backbone segment C
	 */
	void SetBackbone(FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
	/*
	 * creates a rotation matrix from two carbons and an oxygen
	 * @Param C1 first carbon
	 * @Param C2 second carbon, from the next segment
	 * @Param O oxygen from the current segment
	 */
	FMatrix MakeRotation(FAtomData* C1, FAtomData* C2, FAtomData* O);
	/*
	 * update the positions of the backbone atoms dynamically
	 */
	void UpdateBackBone();
private:
	TArray<FAtomData*> Backbone;
	bool IsStartingBackBone = false;
};
