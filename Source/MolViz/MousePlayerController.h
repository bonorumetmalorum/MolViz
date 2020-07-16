// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FArcBall.h"
#include "ProteinRepresentation.h"
#include "GameFramework/PlayerController.h"
#include "MousePlayerController.generated.h"

UENUM()
enum class ETransformMode
{
	Rotate,
	Translate,
	Scale
};

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
	void ModeScale();
	void ModeRotate();
	void ModeTranslate();
	bool Rotating;

	
	UPROPERTY()
	UArcBall * ArcBallController;

	ETransformMode TransformMode;
	
	TWeakObjectPtr<AProteinRepresentation> ProteinRep;
	UPROPERTY()
	FVector CurrentPostion;
	FVector PreviousPosition;
	FVector4 CurrentTranslation;
	FQuat CurrenRotation;
};
