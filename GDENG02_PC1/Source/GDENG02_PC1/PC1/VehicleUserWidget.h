// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UserDefinedDataTypes.h"
#include "Blueprint/UserWidget.h"
#include "VehicleUserWidget.generated.h"


#ifndef LOCTEXT_NAMESPACE
#define LOCTEXT_NAMESPACE "DefaultLocTextNamespace"
#endif


UCLASS(Abstract, Blueprintable)
class GDENG02_PC1_API UVehicleUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
// METHODS
public:
	void SetVehicleID(uint32 ID);
	void SetStorage(TArray<EMaterials>& Materials);

	void SetDestination(EBuildingTypes Type);
	void SetVehicleState(EVehicleStates State);

	void SetLoadingTime(uint32 Time);
	void SetUnloadingTime(uint32 Time);
	void SetTravelTime(uint32 Time);
	void SetElapsedTime(float Time, uint32 MaxTime);


// ATTRIBUTES
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* VehicleID_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* Storage_Text;

	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* Destination_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* VehicleState_Text;

	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* LoadingTime_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* UnloadingTime_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* TravelTime_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UProgressBar* ElapsedTime_Bar;
};
