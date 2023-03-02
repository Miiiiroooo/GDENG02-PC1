// Copyright Epic Games, Inc. All Rights Reserved.


#include "BuildingTriggerBox.h"
#include "VehicleActorComponent.h"
#include "BuildingActorComponent.h"


ABuildingTriggerBox::ABuildingTriggerBox()
{
	this->BuildingActorOfTriggerBox = nullptr;
	this->NextBuildingActorOfTriggerBox = nullptr;
}


void ABuildingTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	if (this->BuildingActorOfTriggerBox != nullptr)
	{
		this->BuildingComponentOfTriggerBox = this->BuildingActorOfTriggerBox->FindComponentByClass<UBuildingActorComponent>();
	}

	if (this->NextBuildingActorOfTriggerBox != nullptr)
	{
		this->NextBuildingComponentOfTriggerBox = this->BuildingActorOfTriggerBox->FindComponentByClass<UBuildingActorComponent>();
	}

	this->OnActorBeginOverlap.AddDynamic(this, &ABuildingTriggerBox::OnBeginOverlapActor);
}


// PRIVATE METHODS
void ABuildingTriggerBox::OnBeginOverlapActor(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != nullptr)
	{
		UVehicleActorComponent* vehicle = OtherActor->FindComponentByClass<UVehicleActorComponent>();

		if (vehicle != nullptr)
		{
			// Check vehicle state and perform the loading/unloading timers
			switch (vehicle->GetVehicleState())
			{
				case EVehicleStates::Fetching:
				{
					FTimerDelegate LoadMaterialDelegate = FTimerDelegate::CreateUObject(this, &ABuildingTriggerBox::OnBeginLoadingMaterialsToVehicle, vehicle);
					this->GetWorldTimerManager().SetTimer(this->BuildingTriggerBoxTimerHandle, LoadMaterialDelegate, vehicle->GetLoadingTime(), false);
					break;
				}
				case EVehicleStates::Delivering:
				{
					FTimerDelegate UnloadMaterialDelegate = FTimerDelegate::CreateUObject(this, &ABuildingTriggerBox::OnBeginUnloadingMaterialsToVehicle, vehicle);
					this->GetWorldTimerManager().SetTimer(this->BuildingTriggerBoxTimerHandle, UnloadMaterialDelegate, vehicle->GetUnloadingTime(), false);
					break;
				}
				default:
				{
					break;
				}
			}

			// Make vehicle stop after initializing the timers
			vehicle->StopVehicle();
		}
	}
}

void ABuildingTriggerBox::OnBeginLoadingMaterialsToVehicle(UVehicleActorComponent* vehicle)
{
	if (this->BuildingComponentOfTriggerBox == nullptr)
		return;

	TArray<EMaterials> materials;

	this->BuildingComponentOfTriggerBox->ExportMaterial(materials);
	vehicle->LoadMaterial(this->NextBuildingActorOfTriggerBox->GetActorLocation(), materials);
}

void ABuildingTriggerBox::OnBeginUnloadingMaterialsToVehicle(UVehicleActorComponent* vehicle)
{
	if (this->BuildingComponentOfTriggerBox == nullptr)
		return;
	
	TArray<EMaterials> materials;
	EMaterials importedMaterial = vehicle->GetMaterialInStorage();

	if (this->BuildingComponentOfTriggerBox->CheckIfInputStorageIsFull(importedMaterial))
	{
		return;
	}

	vehicle->UnloadMaterial(materials);
	this->BuildingComponentOfTriggerBox->ImportMaterial(materials);
}