// Copyright Epic Games, Inc. All Rights Reserved.


#include "PC1_GameMode.h"
#include "PC1_HUD.h"
#include "BuildingActorComponent.h"
#include "VehicleActorComponent.h"
#include "VehicleUserWidget.h"
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

	// Assign HUD
	this->HUD = Cast<APC1_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}


void APC1_GameMode::OnBuildingReadyToExport(UBuildingActorComponent* Building)
{
	if (Building == nullptr)
		return;


	if (!this->BuildingsPendingExportList.Contains(Building))
	{
		this->BuildingsPendingExportList.Add(Building);
	}

	for (auto vehicle : this->VehicleList)
	{
		if (vehicle->IsVehicleAvailableToFetch())
		{
			vehicle->FetchMaterial(Building->GetLocation());
			this->BuildingsPendingExportList.Remove(Building);

			break;
		}
	}
}


void APC1_GameMode::OnVehicleReadyToFetch(UVehicleActorComponent* vehicle)
{
	if (this->BuildingsPendingExportList.Num() != 0)
	{
		vehicle->FetchMaterial(this->BuildingsPendingExportList[0]->GetLocation());
		this->BuildingsPendingExportList.RemoveAt(0);

	}
}