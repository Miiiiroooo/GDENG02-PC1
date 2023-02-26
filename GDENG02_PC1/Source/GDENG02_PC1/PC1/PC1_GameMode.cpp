// Copyright Epic Games, Inc. All Rights Reserved.


#include "PC1_GameMode.h"
#include "VehicleActorComponent.h"
#include "Kismet/GameplayStatics.h"


APC1_GameMode::APC1_GameMode(const FObjectInitializer& ObjectInitializer)
{
	
}

void APC1_GameMode::BeginPlay()
{
	Super::BeginPlay();

	// Get all vehicles in level
	TArray<AActor*> ActorList;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AActor::StaticClass(), ActorList);

	for (auto actor : ActorList)
	{
		UVehicleActorComponent* component = actor->FindComponentByClass<UVehicleActorComponent>();

		if (component != nullptr)
		{
			this->VehicleList.Add(component);
		}
	}
}


void APC1_GameMode::OnBuildingReadyToExport(FVector BuildingLocation)
{
	this->BuildingsPendingExportList.Add(BuildingLocation);

	for (auto vehicle : this->VehicleList)
	{
		if (vehicle->IsVehicleAvailableToFetch())
		{
			vehicle->FetchMaterial(BuildingLocation);
			this->BuildingsPendingExportList.Remove(BuildingLocation);

			break;
		}
	}
}


void APC1_GameMode::OnVehicleReadyToFetch()
{

}