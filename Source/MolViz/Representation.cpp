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
	if (name.Equals("H", ESearchCase::IgnoreCase))
	{
		return AtomType::H;
	}
	if (name.Equals("O", ESearchCase::IgnoreCase))
	{
		return AtomType::O;

	}
	if (name.Equals("N", ESearchCase::IgnoreCase))
	{
		return AtomType::N;

	}
	if (name.Equals("C", ESearchCase::IgnoreCase))
	{
		return AtomType::C;

	}
	if (name.Equals("S", ESearchCase::IgnoreCase))
	{
		return AtomType::S;

	}
	if (name.Equals("P", ESearchCase::IgnoreCase))
	{
		return AtomType::P;

	}
	if (name.Equals("Z", ESearchCase::IgnoreCase))
	{
		return AtomType::Z;

	}
	if (name.Equals("LPA", ESearchCase::IgnoreCase))
	{
		return AtomType::LPA;

	}
	if (name.Equals("LPB", ESearchCase::IgnoreCase))
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

