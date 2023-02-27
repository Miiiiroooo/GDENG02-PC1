// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "UserDefinedDataTypes.h"
#include "BuildingTriggerBox.generated.h"


class UBuildingActorComponent; // forward declaration
class UVehicleActorComponent; // forward declartion


UCLASS()
class GDENG02_PC1_API ABuildingTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	ABuildingTriggerBox();


// METHODS
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION() void OnBeginOverlapActor(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION() void OnBeginLoadingMaterialsToVehicle(UVehicleActorComponent* vehicle);
	UFUNCTION() void OnBeginUnloadingMaterialsToVehicle(UVehicleActorComponent* vehicle);


// ATTRIBUTES
private:
	UPROPERTY(EditAnywhere) AActor* BuildingActorOfTriggerBox;
	UPROPERTY(EditAnywhere) UBuildingActorComponent* BuildingComponentOfTriggerBox;

	UPROPERTY(EditAnywhere) AActor* NextBuildingActorOfTriggerBox;
	UPROPERTY(EditAnywhere) UBuildingActorComponent* NextBuildingComponentOfTriggerBox;

	UPROPERTY() FTimerHandle BuildingTriggerBoxTimerHandle;
};
