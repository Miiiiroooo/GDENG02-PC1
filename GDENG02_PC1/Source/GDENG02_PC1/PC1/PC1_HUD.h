// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PC1_HUD.generated.h"


class UBuildingUserWidget; 
class UVehicleUserWidget;
class UBuildingActorComponent;
class UVehicleActorComponent;


UCLASS()
class GDENG02_PC1_API APC1_HUD : public AHUD
{
	GENERATED_BODY()
	
// METHODS
public:
	APC1_HUD();

	void OnChangeWidget(int32 Change);
	UBuildingUserWidget* GetBuildingWidget();
	UVehicleUserWidget* GetVehicleWidget();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void DisplayWidgetBasedOnIndex();


// ATTRIBUTES
private:
	UPROPERTY(EditAnywhere) TSubclassOf<UBuildingUserWidget> BuildingHUDClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UVehicleUserWidget> VehicleHUDClass;
	UPROPERTY() UBuildingUserWidget* BuildingUserWidget;
	UPROPERTY() UVehicleUserWidget* VehicleUserWidget;
	UPROPERTY() TArray<UBuildingActorComponent*> BuildingList;
	UPROPERTY() TArray<UVehicleActorComponent*> VehicleList;
	UPROPERTY() int32 CurrentIndex;
	UPROPERTY() int32 IndexLimit;
};
