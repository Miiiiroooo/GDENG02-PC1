// Copyright Epic Games, Inc. All Rights Reserved.


#include "VehicleActorComponent.h"
#include "PC1_GameMode.h"
#include "Kismet/GameplayStatics.h"


UVehicleActorComponent::UVehicleActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Default Values
	this->VehicleID = -1;

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


// PROTECTED METHODS
void UVehicleActorComponent::BeginPlay()
{
	Super::BeginPlay();


	// Default Values
	this->StorageLimit = FMath::RandRange((int32)this->StorageLowerLimit, (int32)this->StorageUpperLimit);
	ResetDeliveryTimes();

	this->ElapsedTime = 0.0f;
	this->StartPosition = this->GetComponentLocation();
	this->EndPosition = FVector::ZeroVector;

	this->bIsVehicleAvailableToFetch = true;
	this->VehicleState = EVehicleStates::Idle;


	// Assigning delegates
	APC1_GameMode* GameMode = Cast<APC1_GameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode != nullptr)
	{
		this->OnReadyToFetchDelegate.AddUObject(GameMode, &APC1_GameMode::OnVehicleReadyToFetch);
	}
}


// PUBLIC METHODS
void UVehicleActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	switch (this->VehicleState)
	{
	case EVehicleStates::Fetching:

		OnTravelingState();
		break;

	case EVehicleStates::Delivering:

		OnTravelingState();
		break;

	default:

		break;
	}
}

EVehicleStates UVehicleActorComponent::GetVehicleState()
{
	return this->VehicleState;
}

float UVehicleActorComponent::GetLoadingTime()
{
	return this->LoadingTime;
}

float UVehicleActorComponent::GetUnloadingTime()
{
	return this->UnloadingTime;
}

bool UVehicleActorComponent::IsVehicleAvailableToFetch()
{
	return this->bIsVehicleAvailableToFetch;
}

void UVehicleActorComponent::FetchMaterial(FVector BuildingLocation)
{
	if (this->Storage.Num() < (int32)this->StorageLimit)
	{
		this->bIsVehicleAvailableToFetch = false;
		this->VehicleState = EVehicleStates::Fetching;

		this->StartPosition = this->GetComponentLocation();
		this->EndPosition = BuildingLocation;
	}
}

void UVehicleActorComponent::StopVehicle()
{
	switch (this->VehicleState)
	{
	case EVehicleStates::Fetching:

		this->VehicleState = EVehicleStates::Loading;
		this->ElapsedTime = 0.0f;
		break;

	case EVehicleStates::Delivering:

		this->VehicleState = EVehicleStates::Unloading;
		this->ElapsedTime = 0.0f;
		break;

	default:

		break;
	}
}

void UVehicleActorComponent::LoadMaterial(FVector NextBuildingLocation, TArray<EMaterials>& Materials)
{
	for (int32 i = 0; i < Materials.Num(); i++)
	{
		this->Storage.Add(Materials[0]);
	}

	this->VehicleState = EVehicleStates::Delivering;
	this->StartPosition = this->GetComponentLocation();
	this->EndPosition = NextBuildingLocation;
}

void UVehicleActorComponent::UnloadMaterial(TArray<EMaterials>& Materials)
{
	// Unload every material inside storage into the Materials reference
	for (int32 i = 0; i < this->Storage.Num(); i++)
	{
		Materials.Add(this->Storage[0]);
	}

	// Empty the storage
	this->Storage.Empty();

	// Reset values of vehicle
	ResetDeliveryTimes();
	this->bIsVehicleAvailableToFetch = true;
	this->VehicleState = EVehicleStates::Idle;

	// Call delegate function that vehicle is ready to fetch more materials
	if (this->OnReadyToFetchDelegate.IsBound())
	{
		this->OnReadyToFetchDelegate.Broadcast(this);
	}
}


// PRIVATE METHODS
void UVehicleActorComponent::OnTravelingState()
{
	this->ElapsedTime += this->GetWorld()->GetDeltaSeconds();

	float interpolatedValue = this->ElapsedTime / this->TravelTime;
	FVector newPos = this->StartPosition + interpolatedValue * (this->EndPosition - this->StartPosition);

	this->GetOwner()->SetActorLocation(newPos);
}

void UVehicleActorComponent::ResetDeliveryTimes()
{
	this->LoadingTime = FMath::RandRange((int32)this->LoadingTimeLowerLimit, (int32)this->LoadingTimeUpperLimit);
	this->UnloadingTime = FMath::RandRange((int32)this->UnloadingTimeLowerLimit, (int32)this->UnloadingTimeUpperLimit);
	this->TravelTime = FMath::RandRange((int32)this->TravelTimeLowerLimit, (int32)this->TravelTimeUpperLimit);
}

void UVehicleActorComponent::DeliverMaterial()
{
	this->VehicleState = EVehicleStates::Delivering;
	this->ElapsedTime = 0.0f;
}