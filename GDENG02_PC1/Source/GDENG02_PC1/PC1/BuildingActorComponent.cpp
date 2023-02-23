// Copyright Epic Games, Inc. All Rights Reserved.


#include "BuildingActorComponent.h"
#include "UserDefinedDataTypes.h"


UBuildingActorComponent::UBuildingActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UBuildingActorComponent::BeginPlay()
{
	Super::BeginPlay();

	this->InputLimit = FMath::RandRange(this->InputStorageLimitRange.GetLowerBoundValue(), this->InputStorageLimitRange.GetUpperBoundValue());
	this->OutputLimit = FMath::RandRange(this->OutputStorageLimitRange.GetLowerBoundValue(), this->OutputStorageLimitRange.GetUpperBoundValue());

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
	if (this->OutputStorageCount == this->OutputLimit)
		return;


	if (this->CraftingMaterial1 == EMaterials::Unknown && this->CraftingMaterial2 == EMaterials::Unknown)
	{
		if (this->bHasPendingMaterialForOutput)
		{
			this->bHasPendingMaterialForOutput = false;
			this->OutputStorageCount++;
		}

		this->BuildingState = EBuildingStates::Producing;
		Produce();
	}
	else if (this->InputStorageCount1 != 0 && this->InputStorageCount2 != 0)
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


bool UBuildingActorComponent::CheckIfOutputStorageIsFull()
{
	return (this->OutputStorageCount == this->OutputLimit);
}


FVector UBuildingActorComponent::GetBuildingPosition()
{
	return this->GetComponentTransform().GetLocation();
}