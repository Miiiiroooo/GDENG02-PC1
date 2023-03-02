// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UserDefinedDataTypes.h"
#include "VehicleActorComponent.generated.h"


class UBuildingActorComponent; // forward declaration

DECLARE_MULTICAST_DELEGATE_OneParam(FOnReadyToFetchSignature, UVehicleActorComponent*);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG02_PC1_API UVehicleActorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UVehicleActorComponent();


// METHODS
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() void UpdateHUD();
	UFUNCTION() EVehicleStates GetVehicleState();
	UFUNCTION() EMaterials GetMaterialInStorage();
	UFUNCTION() int32 GetStorageCount();
	UFUNCTION() float GetLoadingTime();
	UFUNCTION() float GetUnloadingTime();

	UFUNCTION() bool IsVehicleAvailableToFetch();
	UFUNCTION() void FetchMaterial(FVector BuildingLocation);
	UFUNCTION() void StopVehicle();
	UFUNCTION() void LoadMaterial(FVector NextBuildingLocation, TArray<EMaterials>& Materials);
	UFUNCTION() void UnloadMaterial(TArray<EMaterials>& Materials);

private:
	UFUNCTION() void OnTravelingState();   // includes both fetching and delivering
	UFUNCTION() void ResetDeliveryTimes();
	UFUNCTION() void DeliverMaterial();

		
// ATTRIBUTES
private:
	// Configurables
	UPROPERTY(EditAnywhere) uint32 VehicleID;
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
	UPROPERTY(VisibleAnywhere) TArray<EMaterials> Storage;

	UPROPERTY(VisibleAnywhere) uint32 LoadingTime;
	UPROPERTY(VisibleAnywhere) uint32 TravelTime;
	UPROPERTY(VisibleAnywhere) uint32 UnloadingTime;
	UPROPERTY(VisibleAnywhere) float ElapsedTime;

	UPROPERTY(VisibleAnywhere) FVector StartPosition;
	UPROPERTY(VisibleAnywhere) FVector EndPosition;

	UPROPERTY(VisibleAnywhere) bool bIsVehicleAvailableToFetch;
	UPROPERTY(VisibleAnywhere) EVehicleStates VehicleState;

	UPROPERTY() class APC1_HUD* HUD;


	// Delegates
	FOnReadyToFetchSignature OnReadyToFetchDelegate;
};
