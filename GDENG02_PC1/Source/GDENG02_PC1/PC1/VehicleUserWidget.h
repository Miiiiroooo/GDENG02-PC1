// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UserDefinedDataTypes.h"
#include "Blueprint/UserWidget.h"
#include "VehicleUserWidget.generated.h"


UCLASS()
class GDENG02_PC1_API UVehicleUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetVehicleID(uint32 ID);

	void SetLoadingTime(float time);
	void SetUnloadingTime(float time);
	void SetTravelTime(float time);
	void SetElapsedTime(float time);

	void SetDestination(EBuildingTypes Type);
	void SetVehicleState(EVehicleStates State);
};
