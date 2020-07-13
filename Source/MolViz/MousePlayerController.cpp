// Fill out your copyright notice in the Description page of Project Settings.


#include "MousePlayerController.h"

AMousePlayerController::AMousePlayerController()
{
	this->bShowMouseCursor = true;
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
	UE_LOG(LogTemp, Warning, TEXT("Rotation started"));
	this->Rotating = true;
}

void AMousePlayerController::RotateEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Rotation Ended"));
	this->Rotating = false;
}

void AMousePlayerController::Zoom(float ScrollValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("scroll started %f"), ScrollValue);
}

void AMousePlayerController::RotateX(float X)
{
	if(Rotating)
		UE_LOG(LogTemp, Warning, TEXT("rotate x started %f"), X);

}

void AMousePlayerController::RotateY(float Y)
{
	if(Rotating)
		UE_LOG(LogTemp, Warning, TEXT("rotate y started %f"), Y);
}

