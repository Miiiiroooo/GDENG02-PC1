// Copyright Epic Games, Inc. All Rights Reserved.


#include "VehicleActorComponent.h"

UVehicleActorComponent::UVehicleActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Default Values
	this->StorageLowerLimit = 2;
	this->StorageUpperLimit = 4;

	this->LoadingTimeLowerLimit = 1;
	this->LoadingTimeUpperLimit = 3;

	this->UnloadingTimeLowerLimit = 1;
	this->UnloadingTimeUpperLimit = 3;

	this->TravelTimeLowerLimit = 4;
	this->TravelTimeUpperLimit = 8;

	/*this->StorageLimitRange.SetLowerBoundValue(2);   <-- causes a crash when compiling
	this->StorageLimitRange.SetUpperBoundValue(4);

	this->LoadingTimeRange.SetLowerBound(1);
	this->LoadingTimeRange.SetUpperBound(3);

	this->UnloadingTimeRange.SetLowerBound(1);
	this->UnloadingTimeRange.SetUpperBound(3);

	this->TravelTimeRange.SetLowerBound(4);
	this->TravelTimeRange.SetUpperBound(8);*/
}


void UVehicleActorComponent::BeginPlay()
{
	Super::BeginPlay();


	this->StorageLimit = FMath::RandRange((int32)this->StorageLowerLimit, (int32)this->StorageUpperLimit);
	ResetDeliveryTimes();

	this->StorageCount = 0;
	this->ElapsedTime = 0.0f;
	this->VehicleState = EVehicleStates::Idle;
}


void UVehicleActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UVehicleActorComponent::ResetDeliveryTimes()
{
	this->LoadingTime = FMath::RandRange((int32)this->LoadingTimeLowerLimit, (int32)this->LoadingTimeUpperLimit);
	this->UnloadingTime = FMath::RandRange((int32)this->UnloadingTimeLowerLimit, (int32)this->UnloadingTimeUpperLimit);
	this->TravelTime = FMath::RandRange((int32)this->TravelTimeLowerLimit, (int32)this->TravelTimeUpperLimit);
}

void UVehicleActorComponent::LoadMaterial()
{

}

void UVehicleActorComponent::UnloadMaterial()
{

}

void UVehicleActorComponent::DeliverMaterial()
{

}

void UVehicleActorComponent::ReceieveNotif(FVector BuildingLocation)
{
	if (this->StorageCount < this->StorageLimit)
	{
		this->VehicleState = EVehicleStates::Fetching;
	}
}