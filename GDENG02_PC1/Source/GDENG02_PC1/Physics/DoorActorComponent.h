// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../PC1/UserDefinedDataTypes.h"
#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "DoorActorComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class GDENG02_PC1_API UDoorActorComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UDoorActorComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION() float GetPressurePlateTotalMass() const;

private:
	UPROPERTY(EditAnywhere) ATriggerVolume* PressurePlate;
	//UPROPERTY(EditAnywhere) AActor* ActorOpener;

	UPROPERTY(EditAnywhere) float OpeningYaw = 90.0f;
	UPROPERTY(EditAnywhere) float ClosingYaw = 0.0f;
	UPROPERTY() float Ticks = 0.0f;
	UPROPERTY() float CLOSING_TIME = 3.0f;
	UPROPERTY() float InitialYaw;
	UPROPERTY() float CurrentYaw;
	UPROPERTY() float TotalMass = 180.0f;

	UPROPERTY(VisibleAnywhere) EDoorStates State = EDoorStates::Closed;
};
