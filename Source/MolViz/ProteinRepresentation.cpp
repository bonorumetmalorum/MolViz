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

// Called when the game starts or when spawned
void AProteinRepresentation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProteinRepresentation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProteinRepresentation::AddAtom(float x, float y, float z)
{
	//const int NumComponents = GetComponents().Num();
	//UE_LOG(LogTemp, Warning, TEXT("Number of components on protein: %d"), NumComponents);
	//UProcSphere * Component = Cast<UProcSphere>(AddComponent(FName("ATOM"), false, FTransform(FVector(x, y, z)), UProcSphere::StaticClass()));
	
	UProcSphere* Component = NewObject<UProcSphere>(this, UProcSphere::StaticClass());
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return;
	}
	Component->RegisterComponent();
	Component->SetWorldLocation(FVector(x, y, z));
	Component->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepWorldTransform);
	Component->GenerateSphere(10, 10, 1);
}

void AProteinRepresentation::CreateNewRepresentation()
{
	AProteinData* Protein = Cast<AMolVizGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->ProteinData;
	for(auto iter = Protein->Residues.CreateConstIterator(); iter.GetIndex() < Protein->Residues.Num(); ++iter)
	{
		for(auto atomiter = iter->atoms.CreateConstIterator(); atomiter.GetIndex() < iter->atoms.Num(); ++atomiter)
		{
			AddAtom((*atomiter)->position.X, (*atomiter)->position.Y, (*atomiter)->position.Z);
		}
	}
}

