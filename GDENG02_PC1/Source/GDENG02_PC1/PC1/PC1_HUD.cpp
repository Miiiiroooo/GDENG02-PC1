// Copyright Epic Games, Inc. All Rights Reserved.


#include "PC1_HUD.h"
#include "BuildingUserWidget.h"
#include "VehicleUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


APC1_HUD::APC1_HUD()
{

}


void APC1_HUD::BeginPlay()
{
	Super::BeginPlay();

	//// Get all vehicles in level
	//TArray<AActor*> ActorList;
	//UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AActor::StaticClass(), ActorList);

	//for (auto actor : ActorList)
	//{
	//	UBuildingActorComponent* buildingComponent = actor->FindComponentByClass<UBuildingActorComponent>();
	//	UVehicleActorComponent* vehicleComponent = actor->FindComponentByClass<UVehicleActorComponent>();

	//	if (buildingComponent != nullptr)
	//	{
	//		this->BuildingList.Add(buildingComponent);
	//	}
	//	else if (vehicleComponent != nullptr)
	//	{
	//		this->VehicleList.Add(vehicleComponent);
	//	}
	//}

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

	// Add one of the widgets to viewport
	if (this->BuildingUserWidget != nullptr)
		this->BuildingUserWidget->AddToViewport();
}

UBuildingUserWidget* APC1_HUD::GetBuildingWidget()
{
	return this->BuildingUserWidget;
}

UVehicleUserWidget* APC1_HUD::GetVehicleWidget()
{
	return this->VehicleUserWidget;
}