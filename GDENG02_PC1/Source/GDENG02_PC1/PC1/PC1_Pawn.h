// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "PC1_Pawn.generated.h"

UCLASS()
class GDENG02_PC1_API APC1_Pawn : public ADefaultPawn
{
	GENERATED_BODY()

public:
	APC1_Pawn();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

private:
	void OnNextWidget();
	void OnPrevWidget();


private:
	const FName NEXT_WIDGET_KEY = "NextWidget";
	const FName PREVIOUS_WIDGET_KEY = "PrevWidget";

	UPROPERTY() class APC1_HUD* HUD;
};
