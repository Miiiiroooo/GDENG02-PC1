// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PC1_GameMode.generated.h"


class UBuildingActorComponent; // forward declaration
class UVehicleActorComponent; // forward declaration


UCLASS( ClassGroup = (Custom) )
class GDENG02_PC1_API APC1_GameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

public:
	APC1_GameMode(const FObjectInitializer& ObjectInitializer);


// Methods
public:
	UFUNCTION() void OnBuildingReadyToExport(UBuildingActorComponent* Building);
	UFUNCTION() void OnVehicleReadyToFetch(UVehicleActorComponent* vehicle);


// Attributes
private:
	UPROPERTY(VisibleAnywhere) TArray<UVehicleActorComponent*> VehicleList;
	UPROPERTY(VisibleAnywhere) TArray<FVector> BuildingsPendingExportList;
};
