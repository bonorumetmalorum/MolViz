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
	this->ArcBallController->Ball_BeginDrag();
	GetMousePosition(CurrentPostion.X, CurrentPostion.Y);
	int32 x, y;
	GetViewportSize(x, y);
	int size = (x > y) ? y : x;
	CurrentPostion.X = (2.0 * CurrentPostion.X - size) / size;
	CurrentPostion.Y = (size - 2.0 * CurrentPostion.Y) / size;
	//UE_LOG(LogTemp, Warning, TEXT("Rotation started at %f %f"), PreviousPosition.X, PreviousPosition.Y);
	ArcBallController->Ball_Mouse(CurrentPostion);
	
		
	//Rotating = true;
	/*float x, y;
	GetMousePosition(x, y);
	PreviousPosition.X = x; PreviousPosition.Y = y;*/
	//DeprojectScreenPositionToWorld(x, y, From, FromDirection);
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
	CurrentPostion.Y = (size - 2.0 * CurrentPostion.Y) / size;
	if(this->ArcBallController->Dragging)
	{
		ArcBallController->Ball_Mouse(CurrentPostion);
		ArcBallController->Ball_Update();
		
		FRotator Rot = ArcBallController->Ball_Value();
		ProteinRep->SetActorRotation(Rot);
	}
	//if(Rotating && ProteinRep.IsValid())
	//{
		/*float x, y;
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
		CurrenRotation *= 10.0;
		To = From;
		ProteinRep->SetActorRotation(CurrenRotation);*/
		//float XPos, YPos;
	//	GetMousePosition(XPos, YPos);
	//	CurrentPostion.X = XPos;
	//	CurrentPostion.Y = YPos;
	//	float XDiff = -1.0 * (CurrentPostion.X - PreviousPosition.X);
	//	float YDiff = 1.0 * (CurrentPostion.Y - PreviousPosition.Y);
	//	if (XDiff == 0 && YDiff == 0)
	//		return;
	//	PreviousPosition.X = CurrentPostion.X;
	//	PreviousPosition.Y = CurrentPostion.Y;
	//	float XRot = 0.1 * YDiff;
	//	float YRot = 0.1 * XDiff;
	//	this->ProteinRep->SetActorRotation(this->ProteinRep->GetActorRotation().Add(XRot, YRot, 0));
	//}
	
}

void AMousePlayerController::RotateY(float YPosition)
{
	//UE_LOG(LogTemp, Warning, TEXT("rotate y started %f"), YPosition);
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

		FRotator Rot = ArcBallController->Ball_Value();
		ProteinRep->SetActorRotation(Rot);
	}
	/*if (Rotating && ProteinRep.IsValid())
	{*/
		//float x, y;
		//GetMousePosition(x, y);
		//DeprojectScreenPositionToWorld(x, y, To, ToDirection);
		//To.Normalize();
		//From.Normalize();
		//FVector cross = FVector::CrossProduct(From, To);
		//cross.Normalize();
		//float theta = acos(FVector::DotProduct(From, To));
		//FQuat Rotation(cross, theta);
		//Rotation.Normalize();
		//CurrenRotation *= Rotation;
		//CurrenRotation.Normalize();
		//CurrenRotation *= 10.0;
		//To = From;
		//ProteinRep->SetActorRotation(CurrenRotation);
		//https://cgmath.blogspot.com/2009/03/arc-ball-rotation-using-quaternion.html
		//
		//
		//Attempt 2
		/*float XPos, YPos;
		GetMousePosition(XPos, YPos);
		CurrentPostion.X = XPos;
		CurrentPostion.Y = YPos;
		float XDiff = -1.0 * (CurrentPostion.X - PreviousPosition.X);
		float YDiff = 1.0 * (CurrentPostion.Y - PreviousPosition.Y);
		if (XDiff == 0 && YDiff == 0)
			return;
		PreviousPosition.X = CurrentPostion.X;
		PreviousPosition.Y = CurrentPostion.Y;
		float XRot = 0.1 * YDiff;
		float YRot = 0.1 * XDiff;
		this->ProteinRep->SetActorRotation(this->ProteinRep->GetActorRotation().Add(XRot, YRot, 0));*/
	/*}*/
}

