// Fill out your copyright notice in the Description page of Project Settings.


#include "MousePlayerController.h"

#include "Kismet/GameplayStatics.h"

AMousePlayerController::AMousePlayerController()
{
	this->bShowMouseCursor = true;
	this->ArcBallController = NewObject<UArcBall>();
	
	ArcBallController->Ball_Place(FVector(0, 0, 0), 0.80);
	this->CurrentPostion = FVector4(0,0,0,1);
	this->PreviousPosition = FVector4(0, 0, 0, 1);
	this->CurrenRotation = FQuat::Identity;
	TransformMode = ETransformMode::Rotate;
}

void AMousePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMousePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("EnableRotation", EInputEvent::IE_Pressed, this, &AMousePlayerController::RotateStart);
	InputComponent->BindAction("EnableRotation", EInputEvent::IE_Released, this, &AMousePlayerController::RotateEnd);
	InputComponent->BindAction("Scale", EInputEvent::IE_Released, this, &AMousePlayerController::ModeScale);
	InputComponent->BindAction("Rotate", EInputEvent::IE_Released, this, &AMousePlayerController::ModeRotate);
	InputComponent->BindAction("Translate", EInputEvent::IE_Released, this, &AMousePlayerController::ModeTranslate);
	InputComponent->BindAxis("Zoom", this, &AMousePlayerController::Zoom);
	InputComponent->BindAxis("RotateX", this, &AMousePlayerController::RotateX);
	InputComponent->BindAxis("RotateY", this, &AMousePlayerController::RotateY);
	
}

void AMousePlayerController::RotateStart()
{
	GetMousePosition(CurrentPostion.X, CurrentPostion.Y);
	int32 x, y;
	GetViewportSize(x, y);
	int size = (x > y) ? y : x;
	CurrentPostion.X = (2.0 * CurrentPostion.X - size) / size;
	CurrentPostion.Y = (size - 2.0 * CurrentPostion.Y) / size;
	//UE_LOG(LogTemp, Warning, TEXT("Rotation started at %f %f"), PreviousPosition.X, PreviousPosition.Y);
	ArcBallController->Ball_Mouse(CurrentPostion);
	this->ArcBallController->Ball_BeginDrag();
}

void AMousePlayerController::RotateEnd()
{
	//UE_LOG(LogTemp, Warning, TEXT("Rotation Ended"));
	this->ArcBallController->Ball_EndDrag();
	Rotating = false;
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
	GetMousePosition(CurrentPostion.X, CurrentPostion.Y);
	int32 x, y;
	GetViewportSize(x, y);
	int size = (x > y) ? y : x;
	CurrentPostion.X = (2.0 * CurrentPostion.X - size) / size;
	CurrentPostion.Y = (size - (2.0 * CurrentPostion.Y)) / size;
	if(this->ArcBallController->Dragging)
	{
		ArcBallController->Ball_Mouse(CurrentPostion);
		ArcBallController->Ball_Update();
		ProteinRep->SetActorRotation(ArcBallController->Ball_Value());
	}
}

void AMousePlayerController::RotateY(float YPosition)
{
	GetMousePosition(CurrentPostion.X, CurrentPostion.Y);
	int32 x, y;
	GetViewportSize(x, y);
	int size = (x > y) ? y : x;
	CurrentPostion.X = (2.0 * CurrentPostion.X - size) / size;
	CurrentPostion.Y = (size - 2.0 * CurrentPostion.Y) / size;
	if(this->ArcBallController->Dragging)
	{
		ArcBallController->Ball_Mouse(CurrentPostion);
		ArcBallController->Ball_Update();

		ProteinRep->SetActorRotation(ArcBallController->Ball_Value());
	}
}

