// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Representation.generated.h"


UCLASS( ClassGroup=(Custom), Abstract )
class MOLVIZ_API URepresentation : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URepresentation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
