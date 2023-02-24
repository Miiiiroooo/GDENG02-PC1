// Copyright Epic Games, Inc. All Rights Reserved.


#include "BuildingActorComponent.h"
#include "UserDefinedDataTypes.h"
#include "VehicleActorComponent.h"
#include "Kismet/GameplayStatics.h"


UBuildingActorComponent::UBuildingActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Default Values
	this->InputLimit = 3;
	this->OutputLimit = 3;
	this->ProductionSpeed = 5.0f;

	this->CraftingMaterial1 = EMaterials::Unknown;
	this->CraftingMaterial2 = EMaterials::Unknown;

	// Assigning delegates
	TArray<AActor*> VehicleList;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AActor::StaticClass(), VehicleList);

	for (auto actor : VehicleList)
	{
		UVehicleActorComponent* component = actor->FindComponentByClass< UVehicleActorComponent>();

		if (component != nullptr)
		{
			this->OnReadyToExportDelegate.AddUObject(component, &UVehicleActorComponent::ReceieveNotif);
		}
	}
}


void UBuildingActorComponent::BeginPlay()
{
	Super::BeginPlay();


	this->InputStorageCount1 = 0;
	this->InputStorageCount2 = 0;
	this->OutputStorageCount = 0;

	this->bHasPendingMaterialForOutput = false;
	this->ElapsedProduction = 0.0f;
	this->BuildingState = EBuildingStates::Waiting;
}


void UBuildingActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (this->BuildingState == EBuildingStates::Waiting)
	{
		CheckIfBuildingCanProduce();
	}
	else if (this->BuildingState == EBuildingStates::Producing)
	{
		Produce();
	}

}


void UBuildingActorComponent::Produce()
{
	this->ElapsedProduction += this->GetWorld()->GetDeltaSeconds();

	if (this->ElapsedProduction >= this->ProductionSpeed)
	{
		// check if storage has space for new product, else place the product as pending for output
		if (this->OutputStorageCount < this->OutputLimit)
		{
			this->OutputStorageCount++;
		}
		else
		{
			this->bHasPendingMaterialForOutput = true;
		}


		this->BuildingState = EBuildingStates::Waiting;
		this->ElapsedProduction = 0;
	}
}

void UBuildingActorComponent::CheckIfBuildingCanProduce()
{
	if (this->OutputStorageCount == this->OutputLimit && this->bHasPendingMaterialForOutput)
		return;


	if (this->CraftingMaterial1 == EMaterials::None && this->CraftingMaterial2 == EMaterials::None)
	{
		if (this->bHasPendingMaterialForOutput)
		{
			this->bHasPendingMaterialForOutput = false;
			this->OutputStorageCount++;
		}

		this->BuildingState = EBuildingStates::Producing;
		Produce();
	}
	else if (this->InputStorageCount1 > 0 && this->InputStorageCount2 > 0)
	{
		if (this->bHasPendingMaterialForOutput)
		{
			this->bHasPendingMaterialForOutput = false;
			this->OutputStorageCount++;
		}

		this->InputStorageCount1--;
		this->InputStorageCount2--;

		this->BuildingState = EBuildingStates::Producing;
		Produce();
	}
}


void UBuildingActorComponent::ImportMaterial(EMaterials material)
{
	if (material == this->CraftingMaterial1 && this->InputStorageCount1 != this->InputLimit)
	{
		this->InputStorageCount1++;
	}
	else if (material == this->CraftingMaterial2 && this->InputStorageCount2 != this->InputLimit)
	{
		this->InputStorageCount2++;
	}
}

void UBuildingActorComponent::ExportMaterial()
{
	this->OutputStorageCount--;
}

bool UBuildingActorComponent::CheckIfInputStorageIsFull(EMaterials material)
{
	bool isStorageFull = true;

	if (material == this->CraftingMaterial1)
	{
		isStorageFull = (this->InputStorageCount1 == this->InputLimit);
	}
	else if (material == this->CraftingMaterial2)
	{
		isStorageFull = (this->InputStorageCount2 == this->InputLimit);
	}

	return isStorageFull;
}

FVector UBuildingActorComponent::GetBuildingPosition()
{
	return this->GetComponentTransform().GetLocation();
}