// Copyright Epic Games, Inc. All Rights Reserved.


#include "PC1_Pawn.h"
#include "PC1_HUD.h"
#include "GameFramework/Pawn.h"


APC1_Pawn::APC1_Pawn()
{
	
}

void APC1_Pawn::BeginPlay()
{
	Super::BeginPlay();

	this->HUD = Cast<APC1_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void APC1_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	this->InputComponent->BindAction(this->NEXT_WIDGET_KEY, IE_Pressed, this, &APC1_Pawn::OnNextWidget);
	this->InputComponent->BindAction(this->PREVIOUS_WIDGET_KEY, IE_Pressed, this, &APC1_Pawn::OnPrevWidget);
}

void APC1_Pawn::OnNextWidget()
{
	this->HUD->OnChangeWidget(1);
}

void APC1_Pawn::OnPrevWidget()
{
	this->HUD->OnChangeWidget(-1);
}