// Fill out your copyright notice in the Description page of Project Settings.


#include "ProteinRepresentation.h"


#include "AppManager.h"
#include "MolVizGameModeBase.h"
#include "UProcSphere.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProteinRepresentation::AProteinRepresentation() : AActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void AProteinRepresentation::ActivateRepresentation(TWeakObjectPtr<URepresentation> Rep)
{
	Rep->SetActive(true);
}

void AProteinRepresentation::DeactivateRepresentation(TWeakObjectPtr<URepresentation> Rep)
{
	Rep->SetActive(false);
}

void AProteinRepresentation::RemoveRep(const TWeakObjectPtr<URepresentation> Representation)
{
	auto Index = this->Representations.Find(Representation);
	Representation->SetVisibility(false, true);
	Representations[Index]->DestroyComponent();
	Representations.Remove(Representation);
	
}

// Called when the game starts or when spawned
void AProteinRepresentation::BeginPlay()
{
	Super::BeginPlay();
	auto Root = NewObject<USceneComponent>();
	Root->RegisterComponent();
	this->RootComponent = Root;
}

// Called every frame
void AProteinRepresentation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

