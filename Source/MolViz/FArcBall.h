// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FArcBall.generated.h"
/**
 * 
 */
UCLASS()
class MOLVIZ_API UArcBall : public UObject
{
	GENERATED_BODY()
	
public:
    UArcBall();
	~UArcBall();
    void Ball_Place(FVector center, double radius);
    void Ball_Mouse(FVector VNow);
    void Ball_Update();
    FQuat Ball_Value();
    void Ball_BeginDrag();
    void Ball_EndDrag();
    FVector4 MouseConstrainToSphere(FVector Mouse, FVector BallCenter, double BallRadius);
    FQuat ArcBallPointToPoint(FVector4 A, FVector4 B);
	void Qt_ToBallPoints(FQuat q, FVector* arcFrom, FVector* arcTo);
	void SetRotation(const FQuat& Quat);
	bool Dragging;

private:
    FVector4 Center;
    double Radius;
    FQuat QNow, QDown, QDrag;
    FVector VNow, VDown, VFrom, VTo, VrFrom, VrTo;
    FMatrix MNow, MDown;
};
