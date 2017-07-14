// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate out launch velocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,false,0,0,ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}	
}
void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator AimAsRotator = AimDirection.Rotation();
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
}
void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	FRotator AimAsRotator = AimDirection.Rotation();
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Turret->AimAzimuth(DeltaRotator.Yaw);
}