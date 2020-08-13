// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FArcBall.generated.h"
/**
 * Manages arcball controller related states
 */
UCLASS()
class MOLVIZ_API UArcBall : public UObject
{
	GENERATED_BODY()
	
public:
    UArcBall();
	~UArcBall();
	/*
	 * positions the arcball in NDC
	 */
    void Ball_Place(FVector center, double radius);
	/*
	 * sets the balls position
	 * @Param VNow balls position right now
	 */
    void Ball_Mouse(FVector VNow);
	/*
	 * update the arcballs rotation
	 */
    void Ball_Update();
	/*
	 * get the arcballs current rotation
	 * @return Quaternion rotation of arcball
	 */
    FQuat Ball_Value();
	/*
	 * start the dragging of the arcball
	 */
    void Ball_BeginDrag();
	/*
	 * ends dragging of the arcball
	 */
    void Ball_EndDrag();
	/*
	 * constrain the position of the mouse on the unit sphere of the arcball
	 * @param Mouse current mouse position
	 * @param BallCenter the center location of the ball
	 * @param the radius the of the ball
	 * @return the mouse position on the sphere
	 */
    FVector4 MouseConstrainToSphere(FVector Mouse, FVector BallCenter, double BallRadius);
	/*
	 * computes a quaternion to rotate point A to point B
	 * @Param A starting position
	 * @Param B ending position
	 * @return quaterion rotation
	 */
    FQuat ArcBallPointToPoint(FVector4 A, FVector4 B);
	/*
	 * converta quaternoin rotation to the start rotation and end rotation
	 * @param q the quaternion rotation
	 * @param arcFrom the start rotation
	 * @param arcTo the end rotation
	 */
	void Qt_ToBallPoints(FQuat q, FVector* arcFrom, FVector* arcTo);
	/*
	 * sets the current rotation of the arcball
	 * @Param Quat the new rotation of the arcball
	 */
	void SetRotation(const FQuat& Quat);
	bool Dragging;

private:
    FVector4 Center;
    double Radius;
    FQuat QNow, QDown, QDrag;
    FVector VNow, VDown, VFrom, VTo, VrFrom, VrTo;
    FMatrix MNow, MDown;
};
