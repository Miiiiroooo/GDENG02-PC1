// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PC1_GameMode.generated.h"


class UVehicleActorComponent; // forward declaration


UCLASS( ClassGroup = (Custom) )
class GDENG02_PC1_API APC1_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APC1_GameMode(const FObjectInitializer& ObjectInitializer);


// Methods
public:
	UFUNCTION() void OnBuildingReadyToExport(FVector BuildingLocation);
	UFUNCTION() void OnVehicleReadyToFetch();


// Attributes
private:
	UPROPERTY(VisibleAnywhere) TArray<UVehicleActorComponent*> VehicleList;
	UPROPERTY(VisibleAnywhere) TArray<FVector> BuildingsPendingExportList;
};
