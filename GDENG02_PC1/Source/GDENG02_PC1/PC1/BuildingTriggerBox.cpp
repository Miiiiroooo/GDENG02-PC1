// Copyright Epic Games, Inc. All Rights Reserved.


#include "BuildingTriggerBox.h"
#include "VehicleActorComponent.h"
#include "BuildingActorComponent.h"


ABuildingTriggerBox::ABuildingTriggerBox()
{

}


void ABuildingTriggerBox::BeginPlay()
{
	if (this->BuildingActorOfTriggerBox != nullptr)
	{
		this->BuildingComponentOfTriggerBox = this->BuildingActorOfTriggerBox->FindComponentByClass<UBuildingActorComponent>();
	}

	if (this->NextBuildingActorOfTriggerBox != nullptr)
	{
		this->NextBuildingComponentOfTriggerBox = this->BuildingActorOfTriggerBox->FindComponentByClass<UBuildingActorComponent>();
	}
}


// PRIVATE METHODS
void ABuildingTriggerBox::OnBeginOverlapActor(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != nullptr)
	{
		UVehicleActorComponent* vehicle = OtherActor->FindComponentByClass<UVehicleActorComponent>();

		if (vehicle != nullptr)
		{
			vehicle->StopVehicle();

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
		}
	}
}

void ABuildingTriggerBox::OnBeginLoadingMaterialsToVehicle(UVehicleActorComponent* vehicle)
{
	TArray<EMaterials> materials;

	this->BuildingComponentOfTriggerBox->ExportMaterial(materials);
	vehicle->LoadMaterial(this->NextBuildingActorOfTriggerBox->GetActorLocation(), materials);
}

void ABuildingTriggerBox::OnBeginUnloadingMaterialsToVehicle(UVehicleActorComponent* vehicle)
{
	TArray<EMaterials> materials;

	vehicle->UnloadMaterial(materials);
	this->BuildingComponentOfTriggerBox->ImportMaterial(materials);
}