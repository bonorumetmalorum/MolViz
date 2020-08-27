// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
 * mouse controller
 * links action events to mouse movements
 */
UCLASS()
class MOLVIZ_API AMousePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
	AMousePlayerController();
	/*
	 * setup the input component, initialize any variables and state
	 */
	void SetupInputComponent() override;
	/*
	 * method start a transformation
	 */
	void TransformStart();
	/*
	 * method end a transformation
	 */
	void TransformEnd();
	/*
	 * method to handle zoom out
	 */
	void ZoomOut();
	/*
	 * method to handle zoom in
	 */
	void ZoomIn();
	/*
	 * rotate the model around X
	 */
	void RotateX(float X);
	/*
	 * rotate the model around y
	 */
	void RotateY(float Y);
	/*
	 * scale the protein
	 */
	void ScaleProtein();
	/*
	 * set the currently toggled protein rep
	 */
	void SetProteinRep(AProteinRepresentation* InProteinRep);
	/*
	 * compute the arcball vector, given a mouse position compute the closest point on the arc ball
	 */
	FVector ComputeArcballVector(int x, int y);
	/*
	 * translate the protein
	 */
	void TranslateProtein();
	/*
	 * handle mouse movements, keeping track of previous and next positions
	 */
	void HandleMouseMovement();
	/*
	 * apply the arcball rotaation to the protein
	 */
	void RotateProtein();
	/*
	 * zoom the protein
	 */
	void Zoom(float ScrollValue);
	/*
	 * switch modes of transformation
	 */
	void ModeScale();
	void ModeRotate();
	void ModeTranslate();
	bool TransformEnabled;

	ETransformMode TransformMode;
	
	TWeakObjectPtr<AProteinRepresentation> ProteinRep;
	UPROPERTY()
	FVector CurrentPostion;
	FVector PreviousPosition;
	FVector4 CurrentTranslation;
	FQuat CurrenRotation;
};
