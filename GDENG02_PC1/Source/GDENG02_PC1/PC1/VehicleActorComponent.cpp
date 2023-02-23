// Copyright Epic Games, Inc. All Rights Reserved.


#include "VehicleActorComponent.h"

UVehicleActorComponent::UVehicleActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UVehicleActorComponent::BeginPlay()
{
	Super::BeginPlay();


	ResetDeliveryTimes();
	this->TravelTime = FMath::RandRange(this->TravelTimeRange.GetLowerBoundValue(), this->TravelTimeRange.GetUpperBoundValue());

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
	this->StorageLimit = FMath::RandRange(this->StorageLimitRange.GetLowerBoundValue(), this->StorageLimitRange.GetUpperBoundValue());
	this->LoadingTime = FMath::RandRange(this->LoadingTimeRange.GetLowerBoundValue(), this->LoadingTimeRange.GetUpperBoundValue());
	this->UnloadingTime = FMath::RandRange(this->UnloadingTimeRange.GetLowerBoundValue(), this->UnloadingTimeRange.GetUpperBoundValue());
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