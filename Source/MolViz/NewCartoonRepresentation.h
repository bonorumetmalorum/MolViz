// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Representation.h"
#include "NewCartoonRepresentation.generated.h"

enum ChainState
{
	Start,
	Middle,
	End,
	Invalid
};

/**
 * 
 */
UCLASS()
class MOLVIZ_API UNewCartoonRepresentation : public URepresentation
{
	GENERATED_BODY()

	void ConstructRepresentation(AProteinData* ProteinData) override;
private:
	template<class T>
	void AddBackBoneComponent(FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom);
	void AddAlphaHelixComponent(ChainState CurrentChainState, FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom);
	void AddBetaSheetComponent(ChainState CurrentChainState, FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom);
	void AddCoilComponent(ChainState CurrentChainState, FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom);

	ChainState UpdateChainState(AProteinData* ProteindData, int CurrentResidue);
};

template <class T>
void UNewCartoonRepresentation::AddBackBoneComponent(FAtomData* StartAtom, FAtomData* ControlAtom, FAtomData* EndAtom)
{
	T* Component = NewObject<T>(this, T::StaticClass());
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return;
	}
	Component->SetStartingBackbone(StartAtom, ControlAtom, EndAtom);
	Component->RegisterComponent();
}
