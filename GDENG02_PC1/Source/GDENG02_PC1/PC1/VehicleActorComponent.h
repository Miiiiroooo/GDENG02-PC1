// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UserDefinedDataTypes.h"
#include "VehicleActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG02_PC1_API UVehicleActorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UVehicleActorComponent();


// METHODS
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION() void ResetDeliveryTimes();
	UFUNCTION() void LoadMaterial();
	UFUNCTION() void UnloadMaterial();
	UFUNCTION() void DeliverMaterial();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() void ReceieveNotif(FVector BuildingLocation);

		
// ATTRIBUTES
private:
	// Configurables
	UPROPERTY(EditAnywhere) uint32 StorageLowerLimit;
	UPROPERTY(EditAnywhere) uint32 StorageUpperLimit;
	UPROPERTY(EditAnywhere) uint32 LoadingTimeLowerLimit;
	UPROPERTY(EditAnywhere) uint32 LoadingTimeUpperLimit;
	UPROPERTY(EditAnywhere) uint32 UnloadingTimeLowerLimit;
	UPROPERTY(EditAnywhere) uint32 UnloadingTimeUpperLimit;
	UPROPERTY(EditAnywhere) uint32 TravelTimeLowerLimit;
	UPROPERTY(EditAnywhere) uint32 TravelTimeUpperLimit;

	/*UPROPERTY(EditAnywhere) FInt32Range StorageLimitRange;
	UPROPERTY(EditAnywhere) FInt32Range LoadingTimeRange;
	UPROPERTY(EditAnywhere) FInt32Range UnloadingTimeRange;
	UPROPERTY(EditAnywhere) FInt32Range TravelTimeRange;*/


	// Normal Vehicle Attributes
	UPROPERTY(VisibleAnywhere) uint32 StorageLimit;
	UPROPERTY(VisibleAnywhere) uint32 StorageCount;

	UPROPERTY(VisibleAnywhere) float LoadingTime;
	UPROPERTY(VisibleAnywhere) float UnloadingTime;
	UPROPERTY(VisibleAnywhere) float TravelTime;
	UPROPERTY(VisibleAnywhere) float ElapsedTime;

	UPROPERTY(VisibleAnywhere) EVehicleStates VehicleState;
};
