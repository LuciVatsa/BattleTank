// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (!ControlledTank) { return; }
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank)
	{
		// move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);
		//aim towards player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//fire when ready

		ControlledTank->Fire(); //fires every frame
		//TODO Control Fire Rate
	}
	else
	{
		return;
	}
}




