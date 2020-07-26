// Fill out your copyright notice in the Description page of Project Settings.

#include "Representation.h"
#include "AProteinData.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
URepresentation::URepresentation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable>ColorData(TEXT("DataTable'/Game/AtomColorData.AtomColorData'"));
	AtomColors = ColorData.Object;
}


// Called when the game starts
void URepresentation::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

AtomType URepresentation::NameToType(FString name)
{
	if (name.Contains("H", ESearchCase::IgnoreCase))
	{
		return AtomType::H;
	}
	if (name.Contains("O", ESearchCase::IgnoreCase))
	{
		return AtomType::O;

	}
	if (name.Contains("N", ESearchCase::IgnoreCase))
	{
		return AtomType::N;

	}
	if (name.Contains("C", ESearchCase::IgnoreCase))
	{
		return AtomType::C;

	}
	if (name.Contains("S", ESearchCase::IgnoreCase))
	{
		return AtomType::S;

	}
	if (name.Contains("P", ESearchCase::IgnoreCase))
	{
		return AtomType::P;

	}
	if (name.Contains("Z", ESearchCase::IgnoreCase))
	{
		return AtomType::Z;

	}
	if (name.Contains("LPA", ESearchCase::IgnoreCase))
	{
		return AtomType::LPA;

	}
	if (name.Contains("LPB", ESearchCase::IgnoreCase))
	{
		return AtomType::LPB;

	}
	return AtomType::O;
}


// Called every frame
void URepresentation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URepresentation::ConstructRepresentation(AProteinData * residues)
{

}

