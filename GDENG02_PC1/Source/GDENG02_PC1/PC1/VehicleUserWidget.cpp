// Copyright Epic Games, Inc. All Rights Reserved.


#include "VehicleUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UVehicleUserWidget::SetVehicleID(uint32 ID)
{
	if (this->VehicleID_Text == nullptr)
		return;


	FText text = FText::Format(LOCTEXT("VehicleID_Key", "VehicleID: {ID}"), ID);
	this->VehicleID_Text->SetText(text);
}

void UVehicleUserWidget::SetStorage(TArray<EMaterials>& Materials)
{
	if (this->Storage_Text == nullptr)
		return;

	FText text;

	if (Materials.Num() == 0)
	{
		text = FText::Format(LOCTEXT("Storage_Key", "Storage: {Item} - {Count}"), UEnum::GetDisplayValueAsText(EMaterials::None), Materials.Num());
	}
	else if (Materials.Num() > 0)
	{
		text = FText::Format(LOCTEXT("Storage_Key", "Storage: {Item} - {Count}"), UEnum::GetDisplayValueAsText(Materials[0]), Materials.Num());
	}

	this->Storage_Text->SetText(text);
}

//void UVehicleUserWidget::SetDestination(EBuildingTypes Type)
//{
//	if (this->Destination_Text == nullptr)
//		return;
//
//
//	FText text = FText::Format(LOCTEXT("Destination_Key", "Destination: {Type}"), UEnum::GetDisplayValueAsText(Type));
//	this->Destination_Text->SetText(text);
//}

void UVehicleUserWidget::SetVehicleState(EVehicleStates State)
{
	if (this->VehicleState_Text == nullptr)
		return;


	FText text = FText::Format(LOCTEXT("VehicleState_Key", "Vehicle State: {State}"), UEnum::GetDisplayValueAsText(State));
	this->VehicleState_Text->SetText(text);
}

void UVehicleUserWidget::SetLoadingTime(uint32 Time)
{
	if (this->LoadingTime_Text == nullptr)
		return;


	FText text = FText::Format(LOCTEXT("LoadingTime_Key", "Loading Time: {time}"), Time);
	this->LoadingTime_Text->SetText(text);
}

void UVehicleUserWidget::SetUnloadingTime(uint32 Time)
{
	if (this->UnloadingTime_Text == nullptr)
		return;


	FText text = FText::Format(LOCTEXT("UnloadingTime_Key", "Unloading Time: {time}"), Time);
	this->UnloadingTime_Text->SetText(text);
}

void UVehicleUserWidget::SetTravelTime(uint32 Time)
{
	if (this->TravelTime_Text == nullptr)
		return;


	FText text = FText::Format(LOCTEXT("TravelTime_Key", "Travel Time: {time}"), Time);
	this->TravelTime_Text->SetText(text);
}

void UVehicleUserWidget::SetElapsedTime(float Time, uint32 MaxTime)
{
	if (this->ElapsedTime_Bar == nullptr)
		return;

	this->ElapsedTime_Bar->SetPercent(Time / (float)MaxTime);
}