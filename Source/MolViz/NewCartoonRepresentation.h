// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BackBoneComponent.h"
#include "CoreMinimal.h"
#include "Representation.h"
#include "NewCartoonRepresentation.generated.h"



/**
 * 
 */
UCLASS()
class MOLVIZ_API UNewCartoonRepresentation : public URepresentation
{
	GENERATED_BODY()

	enum ChainState
	{
		ChainStart,
		ChainMiddle,
		ChainEnd,
		ChainInvalid
	};
public:
	void ConstructRepresentation(AProteinData* ProteinData) override;
	FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
private:
	template<class T>
	T* AddBackBoneComponent(FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
	UBackBoneComponent* AddAlphaHelixComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
	UBackBoneComponent* AddBetaSheetComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
	UBackBoneComponent* AddCoilComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
	FRotator ComputeBackBoneSegementRotation(FAtomData* CarbonA, FAtomData * CarbonB, FAtomData * Oxygen);
	ChainState UpdateChainState(AProteinData* ProteindData, int CurrentResidue);
};

template <class T>
T* UNewCartoonRepresentation::AddBackBoneComponent(FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC)
{
	T* Component = NewObject<T>(this, T::StaticClass());
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return nullptr;
	}
	Component->SetBackbone(CurrentCA, CurrentC, NextCA, NextC);
	Component->RegisterComponent();
	Component->SetMobility(EComponentMobility::Movable);
	Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	return Component;
}
