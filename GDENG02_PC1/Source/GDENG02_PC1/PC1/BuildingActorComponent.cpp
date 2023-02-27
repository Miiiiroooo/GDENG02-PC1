// Copyright Epic Games, Inc. All Rights Reserved.


#include "BuildingActorComponent.h"
#include "UserDefinedDataTypes.h"
#include "PC1_GameMode.h"
#include "Kismet/GameplayStatics.h"


UBuildingActorComponent::UBuildingActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Default Values
	this->BuildingName = "";

	this->InputLimit = 3;
	this->OutputLimit = 3;
	this->ProductionSpeed = 5.0f;

	this->CraftingMaterial1 = EMaterials::Unknown;
	this->CraftingMaterial2 = EMaterials::Unknown;
	this->ProducedMaterial = EMaterials::Unknown;
}


// PROTECTED METHODS
void UBuildingActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Default values
	this->InputStorageCount1 = 0;
	this->InputStorageCount2 = 0;
	this->OutputStorageCount = 0;

	this->bHasPendingMaterialForOutput = false;
	this->ElapsedProduction = 0.0f;
	this->BuildingState = EBuildingStates::Waiting;

	// Assign materials according to the building's type
	AssignMaterialsToBuilding();

	// Assigning delegates
	APC1_GameMode* GameMode = Cast<APC1_GameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode != nullptr)
	{
		this->OnReadyToExportDelegate.AddUObject(GameMode, &APC1_GameMode::OnBuildingReadyToExport);
	}
}


// PUBLIC METHODS
void UBuildingActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	switch (this->BuildingState)
	{
	case EBuildingStates::Waiting:

		CheckIfBuildingCanProduce();
		break;

	case EBuildingStates::Producing:

		Produce();
		break;

	default:

		break;
	}
}

void UBuildingActorComponent::ImportMaterial(TArray<EMaterials>& Materials)
{
	if (Materials[0] == this->CraftingMaterial1 && this->InputStorageCount1 != this->InputLimit)
	{
		this->InputStorageCount1 += Materials.Num();

		// CONDITIONAL CHECK IF INPUT IS FULL BEFORE TAKINF MORE MATERIALS
	}
	else if (Materials[0] == this->CraftingMaterial2 && this->InputStorageCount2 != this->InputLimit)
	{
		this->InputStorageCount2 += Materials.Num();

		// CONDITIONAL CHECK IF INPUT IS FULL BEFORE TAKINF MORE MATERIALS
	}
}

void UBuildingActorComponent::ExportMaterial(TArray<EMaterials>& Materials)
{
	for (uint32 i = 0; i < this->OutputStorageCount; i++)
	{
		Materials.Add(this->ProducedMaterial);
	}

	this->OutputStorageCount = 0;

	// CONDITIONAL CHECK IF OUTPUT REACHES LIMIT OF VEHICLE
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


// PRIVATE METHODS
void UBuildingActorComponent::AssignMaterialsToBuilding()
{
	switch (this->BuildingType)
	{
	case EBuildingTypes::Iron_Mine:

		this->CraftingMaterial1 = EMaterials::None;
		this->CraftingMaterial2 = EMaterials::None;
		this->ProducedMaterial = EMaterials::Iron;
		break;

	case EBuildingTypes::Coal_Mine:

		this->CraftingMaterial1 = EMaterials::None;
		this->CraftingMaterial2 = EMaterials::None;
		this->ProducedMaterial = EMaterials::Coal;
		break;

	case EBuildingTypes::Furnace:

		this->CraftingMaterial1 = EMaterials::Iron;
		this->CraftingMaterial1 = EMaterials::Coal;
		this->ProducedMaterial = EMaterials::Steel_Beam;
		break;

	case EBuildingTypes::Lumberjack_Hut:

		this->CraftingMaterial1 = EMaterials::None;
		this->CraftingMaterial1 = EMaterials::None;
		this->ProducedMaterial = EMaterials::Lumber;
		break;

	case EBuildingTypes::Sewing_Machine_Factory:

		this->CraftingMaterial1 = EMaterials::Steel_Beam;
		this->CraftingMaterial1 = EMaterials::Lumber;
		this->ProducedMaterial = EMaterials::Steel_Beam;

	default:

		this->CraftingMaterial1 = EMaterials::Unknown;
		this->CraftingMaterial1 = EMaterials::Unknown;
		this->ProducedMaterial = EMaterials::Unknown;
		break;
		break;
	}
}

void UBuildingActorComponent::Produce()
{
	this->ElapsedProduction += this->GetWorld()->GetDeltaSeconds();

	if (this->ElapsedProduction >= this->ProductionSpeed)
	{
		// Check current storage if building can add newly produced material in it
		if (this->OutputStorageCount < this->OutputLimit)
		{
			this->OutputStorageCount++;
		}
		else
		{
			this->bHasPendingMaterialForOutput = true;
		}

		// Call the delegate function that building is ready to export
		if (this->OnReadyToExportDelegate.IsBound() && this->ProducedMaterial != EMaterials::Sewing_Machine)
		{
			this->OnReadyToExportDelegate.Broadcast(this->GetComponentLocation());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Delegate not properly configured"));
		}

		// Reset the properties of the building
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
		if (this->bHasPendingMaterialForOutput)    // FIGURE THIS SHIT OUT, TRACE BACK HOW THE BUILDINGS BEHAVE
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
