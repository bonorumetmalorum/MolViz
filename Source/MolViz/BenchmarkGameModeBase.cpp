// Fill out your copyright notice in the Description page of Project Settings.


#include "BenchmarkGameModeBase.h"
#include "StereoRendering.h" 

ABenchmarkGameModeBase::ABenchmarkGameModeBase()
{
	this->SetActorTickEnabled(true);
	
}

TWeakObjectPtr<AProteinData> ABenchmarkGameModeBase::AddProtein()
{
	ProteinDatas.Add(TWeakObjectPtr<AProteinData>(GetWorld()->SpawnActor<AProteinData>()));
	return ProteinDatas.Last();
}

TWeakObjectPtr<AProteinRepresentation> ABenchmarkGameModeBase::AddProteinRep()
{
	ProteinReps.Add(TWeakObjectPtr<AProteinRepresentation>(GetWorld()->SpawnActor<AProteinRepresentation>()));
	return ProteinReps.Last();
}

TWeakObjectPtr<AProteinData> ABenchmarkGameModeBase::AddNewMolecule()
{
	auto ProteinData = AddProtein();
	ProteinData.Get()->Representation = AddProteinRep();
	return ProteinData;
}

void ABenchmarkGameModeBase::SetupNewMolecule()
{
	auto Molecule = AddNewMolecule();
	Reader.readStructure(Path, Molecule.Get());
	RepFactory->CreateNewCpkRep(Molecule->Representation.Get(), Molecule.Get(), FName("CPK"));
	RepFactory->CreateNewTubeRep(Molecule->Representation.Get(), Molecule.Get(), FName("TUBE"));
	this->AtomCount += 4412;
	if (AtomCount > 100000)
	{
		IsFinished = true;
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(NewProteinTimer, this, &ABenchmarkGameModeBase::SetupNewMolecule, 10.0f);
}

void ABenchmarkGameModeBase::ResetProteins()
{
	ProteinReps.Reset();
	ProteinDatas.Reset();
}

void ABenchmarkGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	RepFactory = NewObject<URepresentationFactory>();
	//auto Rep = AddNewMolecule();
	//Reader.readStructure(Path, Rep.Get());
	SetupNewMolecule();
	GetWorld()->GetTimerManager().SetTimer(NewProteinTimer, this, &ABenchmarkGameModeBase::SetupNewMolecule, 10.0f);
}

void ABenchmarkGameModeBase::RotateMolecule(float DeltaSeconds)
{
	if (ProteinReps.Num() > 0)
	{
		ProteinReps[0]->AddActorWorldRotation(FRotator(0.0, 20.0f * DeltaSeconds, 0.0));
	}
}
