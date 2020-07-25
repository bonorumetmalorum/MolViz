// Fill out your copyright notice in the Description page of Project Settings.


#include "FArcBall.h"

UArcBall::UArcBall()
{
    Center = FVector4(0,0,0,1);
    Radius = 0.8;
    VDown = VNow = FVector4(0,0,0,1);
    QDown = QNow = FQuat(0,0,0,1);
    MNow = MDown = FMatrix();
    Dragging = false;
}

UArcBall::~UArcBall()
{
}

void UArcBall::Ball_Place(FVector BallCenter, double Ballradius)
{
    this->Center = BallCenter;
    this->Radius = Ballradius;
}

void UArcBall::Ball_Mouse(FVector MouseVNow)
{
    this->VNow = MouseVNow;
}

void UArcBall::Ball_Update()
{
    VFrom = MouseConstrainToSphere(VDown, Center, Radius);
    VTo = MouseConstrainToSphere(VNow, Center, Radius);
    if (Dragging) {
        QDrag = ArcBallPointToPoint(VFrom, VTo);
        QNow = QDrag * QDown;
    }
    MNow = FRotationMatrix(FRotator(QNow.Inverse()));
}

FQuat UArcBall::Ball_Value()
{
    return QNow.Inverse();
}

void UArcBall::Ball_BeginDrag()
{
    this->Dragging = true;
    VDown = VNow;
}

void UArcBall::Ball_EndDrag()
{
    this->Dragging = false;
    this->QDown = this->QNow;
    this->MDown = MNow;
}


FVector4 UArcBall::MouseConstrainToSphere(FVector Mouse, FVector BallCenter, double BallRadius)
{
    FVector4 BallMouse;
    BallMouse.X = (Mouse.X - BallCenter.X) / BallRadius;
    BallMouse.Y = (Mouse.Y - BallCenter.Y) / BallRadius;
    double Mag = BallMouse.X * BallMouse.X + BallMouse.Y * BallMouse.Y;
    if (Mag > 1.0) {
        double Scale = 1.0 / sqrt(Mag);
        BallMouse.X *= Scale; BallMouse.Y *= Scale;
        BallMouse.Z = 0.0;
    }
    else {
        BallMouse.Z = sqrt(1 - Mag);
    }
    BallMouse.W = 0.0;
    return BallMouse;
}

FQuat UArcBall::ArcBallPointToPoint(FVector4 A, FVector4 B)
{
    FQuat Quat;
    Quat.X = A.Y * B.Z - A.Z * B.Y;
    Quat.Y = A.Z * B.X - A.X * B.Z;
    Quat.Z = A.X * B.Y - A.Y * B.X;
    Quat.W = A.X * B.X + A.Y * B.Y + A.Z * B.Z;
    return Quat;
}

void UArcBall::SetRotation(const FQuat& Quat)
{
    QNow = Quat;
}
