// Fill out your copyright notice in the Description page of Project Settings.


#include "MousePlayerController.h"
#include "GenericPlatform/GenericPlatformMath.h" 
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AMousePlayerController::AMousePlayerController()
{
	this->bShowMouseCursor = true;
	this->CurrentPostion = FVector4(0,0,0,1);
	this->PreviousPosition = FVector4(0, 0, 0, 1);
	this->CurrenRotation = FQuat::Identity;
	this->CurrentTranslation = FVector(0,0,0);
	TransformMode = ETransformMode::Rotate;
}

void AMousePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("EnableTransformation", EInputEvent::IE_Pressed, this, &AMousePlayerController::TransformStart);
	InputComponent->BindAction("EnableTransformation", EInputEvent::IE_Released, this, &AMousePlayerController::TransformEnd);
	InputComponent->BindAction("Scale", EInputEvent::IE_Released, this, &AMousePlayerController::ModeScale);
	InputComponent->BindAction("Rotate", EInputEvent::IE_Released, this, &AMousePlayerController::ModeRotate);
	InputComponent->BindAction("Translate", EInputEvent::IE_Released, this, &AMousePlayerController::ModeTranslate);
	InputComponent->BindAction("ZoomIn", EInputEvent::IE_Pressed, this, &AMousePlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", EInputEvent::IE_Pressed, this, &AMousePlayerController::ZoomOut);
	InputComponent->BindAxis("RotateX", this, &AMousePlayerController::RotateX);
	InputComponent->BindAxis("RotateY", this, &AMousePlayerController::RotateY);
	
}

void AMousePlayerController::TransformStart()
{
	switch(TransformMode)
	{
	case ETransformMode::Scale:
		TransformEnabled = true;
		GetMousePosition(PreviousPosition.X, PreviousPosition.Y);
		break;
	case ETransformMode::Translate:
		TransformEnabled = true;
		break;
	case ETransformMode::Rotate:
		TransformEnabled = true;
		GetMousePosition(CurrentPostion.X, CurrentPostion.Y);
		PreviousPosition.X = CurrentPostion.X; PreviousPosition.Y = CurrentPostion.Y;
	}
	
}

void AMousePlayerController::TransformEnd()
{
	switch (TransformMode)
	{
	case ETransformMode::Translate:
		TransformEnabled = false;
		break;
	case ETransformMode::Scale:
		TransformEnabled = false;
		break;
	case ETransformMode::Rotate:
		TransformEnabled = false;
	}
}

void AMousePlayerController::ZoomOut()
{
	if (ProteinRep.IsValid())
	{
		CurrentTranslation.X += 1.0;
		FTransform CurrentTransform = ProteinRep->GetActorTransform();
		CurrentTransform.SetLocation(CurrentTranslation);
		ProteinRep->SetActorTransform(CurrentTransform);
	}
}

void AMousePlayerController::ZoomIn()
{
	if (ProteinRep.IsValid())
	{
		CurrentTranslation.X -= 1.0;
		FTransform CurrentTransform = ProteinRep->GetActorTransform();
		CurrentTransform.SetLocation(CurrentTranslation);
		ProteinRep->SetActorTransform(CurrentTransform);
	}
}

void AMousePlayerController::TranslateProtein()
{
	if(TransformEnabled)
	{
		float x, y;
		GetInputMouseDelta(x, y);
		float MoveAmount = 1;
		CurrentTranslation += FVector(0, x * MoveAmount, y * MoveAmount);
		ProteinRep->SetActorTransform(FTransform(ProteinRep->GetActorRotation(), CurrentTranslation, ProteinRep->GetActorScale3D()));
	}
}

void AMousePlayerController::HandleMouseMovement()
{
	switch(TransformMode)
	{
	case ETransformMode::Rotate:
		RotateProtein();
		break;
	case ETransformMode::Scale:
		ScaleProtein();
		break;
	case ETransformMode::Translate:
		TranslateProtein();
		break;
	}
}

void AMousePlayerController::RotateProtein()
{
	if(TransformEnabled && ProteinRep.IsValid())
	{
		GetMousePosition(CurrentPostion.X, CurrentPostion.Y);
		if (CurrentPostion.X != PreviousPosition.X || CurrentPostion.Y != PreviousPosition.Y) {
			FVector From = ComputeArcballVector(PreviousPosition.X, PreviousPosition.Y); //from and to vectors on the arcball surface
			FVector To = ComputeArcballVector(CurrentPostion.X, CurrentPostion.Y);
			float Angle = acos(FGenericPlatformMath::Min(1.0f, FVector::DotProduct(From, To))); //the angle between the two vectors
			FVector Axis = FVector::CrossProduct(To, From); //the axis around which we rotate
			Axis.Normalize();
			FQuat Rot(Axis, Angle*5); //create the quaternion rotation to apply
			ProteinRep->AddActorWorldRotation(Rot);
			PreviousPosition.X = CurrentPostion.X;
			PreviousPosition.Y = CurrentPostion.Y;
		}
	}
}

void AMousePlayerController::ModeScale()
{
	TransformMode = ETransformMode::Scale;
}

void AMousePlayerController::ModeRotate()
{
	TransformMode = ETransformMode::Rotate;
}

void AMousePlayerController::ModeTranslate()
{
	TransformMode = ETransformMode::Translate;
}

void AMousePlayerController::RotateX(float XPosition)
{
	HandleMouseMovement();
}

void AMousePlayerController::RotateY(float YPosition)
{
	HandleMouseMovement();
}

void AMousePlayerController::ScaleProtein()
{
	if(TransformEnabled)
	{
		GetMousePosition(CurrentPostion.X, CurrentPostion.Y);
		FVector CurrentScale = ProteinRep->GetActorScale();
		float ScaleMax = 1.0;
		CurrentScale += FVector((CurrentPostion.X - PreviousPosition.X) *ScaleMax, (CurrentPostion.X - PreviousPosition.X) *ScaleMax, (CurrentPostion.X - PreviousPosition.X)*ScaleMax);
		PreviousPosition = CurrentPostion;
		ProteinRep->SetActorTransform(FTransform(ProteinRep->GetActorRotation(), ProteinRep->GetActorLocation(), CurrentScale));
	}
}

void AMousePlayerController::SetProteinRep(AProteinRepresentation * InProteinRep)
{
	this->ProteinRep = InProteinRep;
	CurrentTranslation = InProteinRep->GetTransform().GetTranslation();
}

FVector AMousePlayerController::ComputeArcballVector(int x, int y) {
	int ViewportWidth, ViewportHeight; //viewport width and height
	GetViewportSize(ViewportWidth, ViewportHeight);
	//scale the mouse between -1 and 1 such that we can compute the closest point on the arcball (which is a unit sphere)
	FVector MouseScaled = FVector(1.0 * x / ViewportWidth * 2 - 1.0, 1.0 * y / ViewportHeight * 2 - 1.0,0);
	MouseScaled.Y = -MouseScaled.Y; //invert the y to help with orientation
	float SquaredLength = MouseScaled.X * MouseScaled.X + MouseScaled.Y * MouseScaled.Y; //compute the squared length so we do not incur cost of sqrt op
	if (SquaredLength <= 1) //if it is less than unit length, do not normalize
		MouseScaled.Z = sqrt(1 - SquaredLength); //compute the 3d coordinate on the surface of the sphere using pythagoras
	else
		MouseScaled.Normalize(); //if it is not unit length normalize it, retuning the nearest point
	return MouseScaled;
}