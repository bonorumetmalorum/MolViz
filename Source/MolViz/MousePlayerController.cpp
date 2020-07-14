// Fill out your copyright notice in the Description page of Project Settings.


#include "MousePlayerController.h"

#include "Kismet/GameplayStatics.h"

AMousePlayerController::AMousePlayerController()
{
	this->bShowMouseCursor = true;
	this->ArcBallController = NewObject<UArcBall>();
	ArcBallController->Ball_Place(FVector(0, 0, 0), 0.80);
	this->From = FVector4(0,0,0,1);
	this->To = FVector4(0, 0, 0, 1);
	this->CurrenRotation = FQuat::Identity;
	
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
	InputComponent->BindAxis("Zoom", this, &AMousePlayerController::Zoom);
	InputComponent->BindAxis("RotateX", this, &AMousePlayerController::RotateX);
	InputComponent->BindAxis("RotateY", this, &AMousePlayerController::RotateY);
}

void AMousePlayerController::RotateStart()
{
	/*this->ArcBallController->Ball_BeginDrag();
	GetMousePosition(CurrentMouseLocation.X, CurrentMouseLocation.Y);
	int32 x, y;
	GetViewportSize(x, y);
	int size = (x > y) ? y : x;
	CurrentMouseLocation.X = (2.0 * CurrentMouseLocation.X - size) / size;
	CurrentMouseLocation.Y = (size - 2.0 * CurrentMouseLocation.Y) / size;
	UE_LOG(LogTemp, Warning, TEXT("Rotation started at %f %f"), CurrentMouseLocation.X, CurrentMouseLocation.Y);
	ArcBallController->Ball_Mouse(CurrentMouseLocation);*/
	Rotating = true;
	float x, y;
	GetMousePosition(x, y);
	DeprojectScreenPositionToWorld(x, y, From, FromDirection);
}

void AMousePlayerController::RotateEnd()
{
	/*UE_LOG(LogTemp, Warning, TEXT("Rotation Ended"));
	this->ArcBallController->Ball_EndDrag();*/
	Rotating = false;
}

void AMousePlayerController::Zoom(float ScrollValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("scroll started %f"), ScrollValue);
	CurrentTranslation.X += ScrollValue;
	ProteinRep->AddActorWorldTransform(FTransform(CurrentTranslation));
}

void AMousePlayerController::RotateX(float X)
{
	/*if(this->ArcBallController->Dragging)
	{
		UE_LOG(LogTemp, Warning, TEXT("rotate x started %f"), X);
		CurrentMouseLocation.X = X;
		int32 x, y;
		GetViewportSize(x, y);
		int size = (x > y) ? y : x;
		CurrentMouseLocation.X = (2.0 * CurrentMouseLocation.X - size) / size;
		ArcBallController->Ball_Mouse(CurrentMouseLocation);
		ArcBallController->Ball_Update();
		FRotator Rot = ArcBallController->Ball_Value();
		ProteinRep->SetActorRotation(Rot);
	}*/
	if(Rotating)
	{
		float x, y;
		GetMousePosition(x, y);
		DeprojectScreenPositionToWorld(x, y, To, ToDirection);
		To.Normalize();
		From.Normalize();
		FVector cross = FVector::CrossProduct(From, To);
		cross.Normalize();
		float theta = acos(FVector::DotProduct(From, To));
		FQuat Rotation(cross, theta);
		Rotation.Normalize();
		CurrenRotation *= Rotation;
		CurrenRotation.Normalize();
		To = From;
		ProteinRep->SetActorRotation(CurrenRotation);
	}
	
}

void AMousePlayerController::RotateY(float Y)
{
	/*if(this->ArcBallController->Dragging)
	{
		UE_LOG(LogTemp, Warning, TEXT("rotate y started %f"), Y);
		CurrentMouseLocation.Y = Y;
		int32 x, y;
		GetViewportSize(x, y);
		int size = (x > y) ? y : x;
		CurrentMouseLocation.Y = (size - 2.0 * CurrentMouseLocation.Y) / size;
		ArcBallController->Ball_Mouse(CurrentMouseLocation);
		FRotator Rot = ArcBallController->Ball_Value();
		ProteinRep->SetActorRotation(Rot);
	}*/
	if (Rotating)
	{
		float x, y;
		GetMousePosition(x, y);
		DeprojectScreenPositionToWorld(x, y, To, ToDirection);
		To.Normalize();
		From.Normalize();
		FVector cross = FVector::CrossProduct(From, To);
		cross.Normalize();
		float theta = acos(FVector::DotProduct(From, To));
		FQuat Rotation(cross, theta);
		Rotation.Normalize();
		CurrenRotation *= Rotation * 2.0;
		CurrenRotation.Normalize();
		To = From;
		ProteinRep->SetActorRotation(CurrenRotation);
		//https://cgmath.blogspot.com/2009/03/arc-ball-rotation-using-quaternion.html
	}
}

