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
	void TransformStart();
	void TransformEnd();
	void ZoomOut();
	void ZoomIn();
	void RotateX(float X);
	void RotateY(float Y);
	void ScaleProtein();
	void SetProteinRep(AProteinRepresentation* InProteinRep);
	void TranslateProtein();
	void HandleMouseMovement();
	void RotateProtein();
	void Zoom(float ScrollValue);
	void ModeScale();
	void ModeRotate();
	void ModeTranslate();
	bool TransformEnabled;

	
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
