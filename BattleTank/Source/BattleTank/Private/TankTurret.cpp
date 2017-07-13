// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"



void UTankTurret::AimAzimuth(float RelativeSpeed)
{

	auto AzimuthChange = FMath::Clamp<float>(RelativeSpeed, -1, 1)*MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	auto YawChange = RelativeRotation.Yaw + AzimuthChange;
	SetRelativeRotation(FRotator(0,YawChange,0));
}

