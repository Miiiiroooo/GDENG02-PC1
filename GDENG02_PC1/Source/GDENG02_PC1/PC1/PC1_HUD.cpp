// Copyright Epic Games, Inc. All Rights Reserved.


#include "PC1_HUD.h"
#include "BuildingUserWidget.h"
#include "VehicleUserWidget.h"
#include "BuildingActorComponent.h"
#include "VehicleActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


APC1_HUD::APC1_HUD()
{

}

void APC1_HUD::BeginPlay()
{
	Super::BeginPlay();

	// Get all vehicles in level
	TArray<AActor*> ActorList;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AActor::StaticClass(), ActorList);

	for (auto actor : ActorList)
	{
		UBuildingActorComponent* buildingComponent = actor->FindComponentByClass<UBuildingActorComponent>();
		UVehicleActorComponent* vehicleComponent = actor->FindComponentByClass<UVehicleActorComponent>();

		if (buildingComponent != nullptr)
		{
			this->BuildingList.Add(buildingComponent);
		}
		else if (vehicleComponent != nullptr)
		{
			this->VehicleList.Add(vehicleComponent);
		}
	}

	// Initialize Widgets
	if (this->BuildingHUDClass != nullptr)
	{
		this->BuildingUserWidget = CreateWidget<UBuildingUserWidget>(GetWorld(), this->BuildingHUDClass);

		if (this->BuildingUserWidget == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Building Widget not initialized"));
		}
	}

	if (this->VehicleHUDClass != nullptr)
	{
		this->VehicleUserWidget = CreateWidget<UVehicleUserWidget>(GetWorld(), this->VehicleHUDClass);

		if (this->VehicleUserWidget == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Vehicle Widget not initialized"));
		}
	}

	// Initialize indices
	this->CurrentIndex = 0;
	this->IndexLimit = this->BuildingList.Num() + this->VehicleList.Num();

	// Add one of the widgets to viewport
	DisplayWidgetBasedOnIndex();
}

void APC1_HUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	DisplayWidgetBasedOnIndex();
}

void APC1_HUD::OnChangeWidget(int32 Change)
{
	this->CurrentIndex += Change;

	if (this->CurrentIndex < 0)
	{
		this->CurrentIndex = this->IndexLimit - 1;
	}
	else if (this->CurrentIndex >= this->IndexLimit)
	{
		this->CurrentIndex = 0;
	}
}

UBuildingUserWidget* APC1_HUD::GetBuildingWidget()
{
	return this->BuildingUserWidget;
}

UVehicleUserWidget* APC1_HUD::GetVehicleWidget()
{
	return this->VehicleUserWidget;
}

void APC1_HUD::DisplayWidgetBasedOnIndex()
{
	if (this->CurrentIndex < this->BuildingList.Num())
	{
		for (int32 i = 0; i < this->BuildingList.Num(); i++)
		{
			if (i == this->CurrentIndex)
			{
				this->BuildingList[i]->UpdateHUD();
			}
		}

		if (this->BuildingUserWidget != nullptr && this->VehicleUserWidget != nullptr && !this->BuildingUserWidget->IsInViewport())
		{
			this->BuildingUserWidget->AddToViewport();
			this->VehicleUserWidget->RemoveFromParent();
		}
	}
	else
	{
		for (int32 i = 0; i < this->VehicleList.Num(); i++)
		{
			if (i == this->CurrentIndex - this->BuildingList.Num())
			{
				this->VehicleList[i]->UpdateHUD();
			}
		}

		if (this->BuildingUserWidget != nullptr && this->VehicleUserWidget != nullptr && !this->VehicleUserWidget->IsInViewport())
		{
			this->VehicleUserWidget->AddToViewport();
			this->BuildingUserWidget->RemoveFromParent();
		}
	}
}