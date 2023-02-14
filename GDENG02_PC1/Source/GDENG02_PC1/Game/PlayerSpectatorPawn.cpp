// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpectatorPawn.h"

// Sets default values
APlayerSpectatorPawn::APlayerSpectatorPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerSpectatorPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerSpectatorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

