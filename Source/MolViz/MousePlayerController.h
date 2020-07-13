// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MousePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MOLVIZ_API AMousePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
	AMousePlayerController();

	void Tick(float DeltaSeconds) override;
	void SetupInputComponent() override;
	void RotateStart();
	void RotateEnd();
	void RotateX(float X);
	void RotateY(float Y);
	void Zoom(float ScrollValue);
	bool Rotating;
};
