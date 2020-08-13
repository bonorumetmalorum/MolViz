// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BackBoneComponent.h"
#include "CoreMinimal.h"
#include "Representation.h"
#include "NewCartoonRepresentation.generated.h"



/**
 * New cartoon representation
 */
UCLASS()
class MOLVIZ_API UNewCartoonRepresentation : public URepresentation
{
	GENERATED_BODY()
	// enum to keep track of what part of the chain we are rendering
	enum ChainState
	{
		ChainStart,
		ChainMiddle,
		ChainEnd,
		ChainInvalid
	};
public:
	/*
	 * construct the representation
	 * @param ProteinData the protein data to render
	 */
	void ConstructRepresentation(AProteinData* ProteinData) override;
	/*
	 * calculated sphere bounds
	 */
	FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
private:
	/*
	 * add a new backbone segment
	 * @param CurrentCA the current alpha carbon
	 * @param CurrentC the current carbon
	 * @param NextCA the next alpha carbon
	 * @param NextC the next carbon
	 * @template T the backbone component type
	 * @return the backbone component that was added
	 */
	template<class T>
	T* AddBackBoneComponent(FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
	/*
	 * add a new alpha helix component
	 * @param CurrentChainState what part of the chain are we rendering
	 * @param CurrentCA the current alpha carbon
	 * @param CurrentC the current carbon
	 * @param NextCA the next alpha carbon
	 * @param NextC the next carbon
	 * @return the backbone component that was added
	 */
	UBackBoneComponent* AddAlphaHelixComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
	/*
	 * add a new beta sheet component
	 * @param CurrentChainState what part of the chain are we rendering
	 * @param CurrentCA the current alpha carbon
	 * @param CurrentC the current carbon
	 * @param NextCA the next alpha carbon
	 * @param NextC the next carbon
	 * @return the backbone component that was added
	 */
	UBackBoneComponent* AddBetaSheetComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
	/*
	 * add a new coil component
	 * @param CurrentChainState what part of the chain are we rendering
	 * @param CurrentCA the current alpha carbon
	 * @param CurrentC the current carbon
	 * @param NextCA the next alpha carbon
	 * @param NextC the next carbon
	 * @return the backbone component that was added
	 */
	UBackBoneComponent* AddCoilComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
	/*
	 * compute the segments rotation
	 * @param CarbonA the first carbon atom
	 * @param CarbonN the second carbon atom
	 * @param Oxygen the oxygen atom
	 * @return the rotation of this segment
	 */
	FRotator ComputeBackBoneSegementRotation(FAtomData* CarbonA, FAtomData * CarbonB, FAtomData * Oxygen);
	/*
	 * update the chain state depending on the previous residue type and the next residue type
	 * @param ProteinData the protein data that will the chain will be updated from
	 * @param CurrentResidue the current residue
	 * @return the new chainstate
	 */
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
