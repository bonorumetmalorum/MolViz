// Fill out your copyright notice in the Description page of Project Settings.


#include "MousePlayerController.h"

#include "Kismet/GameplayStatics.h"

AMousePlayerController::AMousePlayerController()
{
	this->bShowMouseCursor = true;
	this->ArcBallController = NewObject<UArcBall>();
	
	ArcBallController->Ball_Place(FVector4(0, 0, 0, 1), 1.0);
	this->CurrentPostion = FVector4(0,0,0,1);
	this->PreviousPosition = FVector4(0, 0, 0, 1);
	this->CurrenRotation = FQuat::Identity;
	this->CurrentTranslation = FVector(0,0,0);
	TransformMode = ETransformMode::Rotate;
}

void AMousePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMousePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("EnableTransformation", EInputEvent::IE_Pressed, this, &AMousePlayerController::TransformStart);
	InputComponent->BindAction("EnableTransformation", EInputEvent::IE_Released, this, &AMousePlayerController::TransformEnd);
	InputComponent->BindAction("Scale", EInputEvent::IE_Released, this, &AMousePlayerController::ModeScale);
	InputComponent->BindAction("Rotate", EInputEvent::IE_Released, this, &AMousePlayerController::ModeRotate);
	InputComponent->BindAction("Translate", EInputEvent::IE_Released, this, &AMousePlayerController::ModeTranslate);
	InputComponent->BindAxis("Zoom", this, &AMousePlayerController::Zoom);
	InputComponent->BindAxis("RotateX", this, &AMousePlayerController::RotateX);
	InputComponent->BindAxis("RotateY", this, &AMousePlayerController::RotateY);
	
}

void AMousePlayerController::TransformStart()
{
	switch(TransformMode)
	{
	case ETransformMode::Scale:
		TransformEnabled = true;

		break;
	case ETransformMode::Translate:
		TransformEnabled = true;
		break;
	case ETransformMode::Rotate:
		GetMousePosition(CurrentPostion.X, CurrentPostion.Y);
		int32 x, y;
		GetViewportSize(x, y);
		int size = (x > y) ? y : x;
		CurrentPostion.X = (2.0 * CurrentPostion.X - size) / size;
		CurrentPostion.Y = (size - 2.0 * CurrentPostion.Y) / size;
		ArcBallController->Ball_Mouse(CurrentPostion);
		this->ArcBallController->Ball_BeginDrag();
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
		ArcBallController->Ball_EndDrag();
		//PreviousPosition = CurrentPostion;
		TransformEnabled = false;
	}
}

void AMousePlayerController::ZoomOut()
{
	if (ProteinRep.IsValid())
	{
		CurrentTranslation.X += 1.0;
		ProteinRep->SetActorTransform(FTransform(CurrentTranslation));
	}
}

void AMousePlayerController::ZoomIn()
{
	if (ProteinRep.IsValid())
	{
		CurrentTranslation.X -= 1.0;
		ProteinRep->SetActorTransform(FTransform(CurrentTranslation));
	}
}

void AMousePlayerController::TranslateProtein()
{
	if(TransformEnabled)
	{
		float x, y;
		//int vx, vy;
		GetInputMouseDelta(x, y);
		//GetViewportSize(vx, vy);
		/*x = ((x / vx) * 2) - 1;
		y = ((y / vy) * 2) - 1;*/
		float MoveAmount = 1;
		CurrentTranslation += FVector(0, x * MoveAmount, y * MoveAmount);
		ProteinRep->SetActorTransform(FTransform(CurrentTranslation));
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
	//if(Rotating)
	//{
	//	GetMousePosition(CurrentPostion.X, CurrentPostion.Y);
	//	FVector To, ToDirection, From, FromDirection;
	//	DeprojectScreenPositionToWorld(CurrentPostion.X, CurrentPostion.Y, To, ToDirection);
	//	DeprojectScreenPositionToWorld(PreviousPosition.X, PreviousPosition.Y, From, FromDirection);
	//	To.Y = -To.Y;
	//	From.Y = -From.Y;
	//	From.Normalize();
	//	To.Normalize();
	//	FVector CrossAxis = FVector::CrossProduct(From, To);
	//	CrossAxis.Normalize();
	//	float Theta = acos(FVector::DotProduct(From, To));
	//	FQuat Rotation(CrossAxis, Theta);
	//	Rotation.Normalize();
	//	PreviousPosition = CurrentPostion;
	//	CurrenRotation *= Rotation;
	//	ProteinRep->SetActorRotation(CurrenRotation);
	//}
	GetMousePosition(CurrentPostion.X, CurrentPostion.Y);
	int32 x, y;
	GetViewportSize(x, y);
	int size = (x > y) ? y : x;
	CurrentPostion.X = (2.0 * CurrentPostion.X - size) / size;
	CurrentPostion.Y = (size - (2.0 * CurrentPostion.Y)) / size;
	if (this->ArcBallController->Dragging)
	{
		ArcBallController->Ball_Mouse(CurrentPostion);
		ArcBallController->Ball_Update();
		ProteinRep->SetActorRotation(ArcBallController->Ball_Value());
	}
	
}

void AMousePlayerController::Zoom(float ScrollValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("scroll started %f"), ScrollValue);
	if(ProteinRep.IsValid())
	{
		CurrentTranslation.X += ScrollValue;
		ProteinRep->AddActorWorldTransform(FTransform(CurrentTranslation));
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
		float x, y;
		int vx, vy;
		GetMousePosition(x, y);
		GetViewportSize(vx, vy);
		x = ((x/vx)*2)-1;
		FVector CurrentScale = ProteinRep->GetActorScale();
		float ScaleMax = 10.0;
		CurrentScale += FVector(x*ScaleMax,x*ScaleMax,x*ScaleMax);
		ProteinRep->SetActorRelativeScale3D(CurrentScale);
	}
}

