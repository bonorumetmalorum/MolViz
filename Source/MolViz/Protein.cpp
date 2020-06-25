// Fill out your copyright notice in the Description page of Project Settings.


#include "Protein.h"

#include "UProcSphere.h"

// Sets default values
AProtein::AProtein() : AActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProtein::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProtein::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProtein::AddAtom(float x, float y, float z)
{
	const int NumComponents = GetComponents().Num();
	UE_LOG(LogTemp, Warning, TEXT("Number of components on protein: %d"), NumComponents);
	//UProcSphere * Component = Cast<UProcSphere>(AddComponent(FName("ATOM"), false, FTransform(FVector(x, y, z)), UProcSphere::StaticClass()));
	UProcSphere* Component = NewObject<UProcSphere>(this, UProcSphere::StaticClass(),"Atom");
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add component"));
		return;
	}
	Component->RegisterComponent();
	Component->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
	Component->AddRelativeLocation(FVector(x, y, x));
	Component->GenerateSphere(10, 10, 10);
}

