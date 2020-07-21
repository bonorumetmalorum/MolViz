// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
		Start,
		Middle,
		End,
		Invalid
	};
public:
	void ConstructRepresentation(AProteinData* ProteinData) override;
private:
	template<class T>
	void AddBackBoneComponent(FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
	void AddAlphaHelixComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
	void AddBetaSheetComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);
	void AddCoilComponent(ChainState CurrentChainState, FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC);

	ChainState UpdateChainState(AProteinData* ProteindData, int CurrentResidue);
};

template <class T>
void UNewCartoonRepresentation::AddBackBoneComponent(FAtomData* CurrentCA, FAtomData* CurrentC, FAtomData* NextCA, FAtomData* NextC)
{
	T* Component = NewObject<T>(this, T::StaticClass());
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return;
	}
	Component->SetBackbone(CurrentCA, CurrentC, NextCA, NextC);
	Component->RegisterComponent();
	Component->SetMobility(EComponentMobility::Movable);
	Component->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
}
