// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PC1_HUD.generated.h"


class UUserWidget; // forward declaration
class UBuildingUserWidget; 
class UVehicleUserWidget;


UCLASS()
class GDENG02_PC1_API APC1_HUD : public AHUD
{
	GENERATED_BODY()
	
// METHODS
public:
	APC1_HUD();

	UBuildingUserWidget* GetBuildingWidget();
	UVehicleUserWidget* GetVehicleWidget();

protected:
	virtual void BeginPlay() override;


// ATTRIBUTES
private:
	UPROPERTY(EditAnywhere) TSubclassOf<UBuildingUserWidget> BuildingHUDClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UVehicleUserWidget> VehicleHUDClass;
	UPROPERTY() UBuildingUserWidget* BuildingUserWidget;
	UPROPERTY() UVehicleUserWidget* VehicleUserWidget;
};
