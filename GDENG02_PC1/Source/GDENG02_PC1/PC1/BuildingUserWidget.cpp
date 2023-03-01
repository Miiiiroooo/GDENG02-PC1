// Copyright Epic Games, Inc. All Rights Reserved.


#include "BuildingUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UBuildingUserWidget::SetBuildingName(FName BuildingName)
{
	if (this->BuildingName_Text == nullptr)
		return;


	this->BuildingName_Text->SetText(FText::FromName(BuildingName));
}

void UBuildingUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->CraftingMaterial1 = EMaterials::Unknown;
	this->CraftingMaterial2 = EMaterials::Unknown;
	this->ProducedMaterial = EMaterials::Unknown;
}

void UBuildingUserWidget::SetCraftingMaterial1(EMaterials Material)
{
	this->CraftingMaterial1 = Material;
}

void UBuildingUserWidget::SetCraftingMaterial2(EMaterials Material)
{
	this->CraftingMaterial2 = Material;
}

void UBuildingUserWidget::SetProducedMaterial(EMaterials Material)
{
	this->ProducedMaterial = Material;
}

void UBuildingUserWidget::SetInputStorage1Text(uint32 Count, uint32 Limit)
{
	if (this->InputStorage1_Text == nullptr && this->CraftingMaterial1 == EMaterials::Unknown)
		return;


	FText text = FText::Format(LOCTEXT("InputStorage1_Key", "Crafting Material ({Material}): {Count} / {Limit}"), UEnum::GetDisplayValueAsText(this->CraftingMaterial1), Count, Limit);
	this->InputStorage1_Text->SetText(text);
}

void UBuildingUserWidget::SetInputStorage2Text(uint32 Count, uint32 Limit)
{
	if (this->InputStorage2_Text == nullptr && this->CraftingMaterial2 == EMaterials::Unknown)
		return;
	

	FText text = FText::Format(LOCTEXT("InputStorage2_Key", "Crafting Material ({Material}): {Count} / {Limit}"), UEnum::GetDisplayValueAsText(this->CraftingMaterial2), Count, Limit);
	this->InputStorage2_Text->SetText(text);
}

void UBuildingUserWidget::SetOutputStorageText(uint32 Count, uint32 Limit)
{
	if (this->OutputStorage_Text == nullptr && this->ProducedMaterial == EMaterials::Unknown)
		return;


	FText text = FText::Format(LOCTEXT("OutputStorage_Key", "Produced Material ({Material}): {Count} / {Limit}"), UEnum::GetDisplayValueAsText(this->ProducedMaterial), Count, Limit);
	this->OutputStorage_Text->SetText(text);
}

void UBuildingUserWidget::SetBuildingState(EBuildingStates State)
{
	if (this->BuildingState_Text == nullptr)
		return;


	FText text = FText::Format(LOCTEXT("BuildingState_Key", "Building State: {State}"), UEnum::GetDisplayValueAsText(State));
	this->BuildingState_Text->SetText(text);
}

void UBuildingUserWidget::SetProductionSpeed(float ProductionSpeed)
{
	if (this->ProductionSpeed_Text == nullptr)
		return;


	FText text = FText::Format(LOCTEXT("ProductionSpeed_Key", "Production Speed: 1 {Produce} / {ProductionSpeed}s"), UEnum::GetDisplayValueAsText(this->ProducedMaterial), ProductionSpeed);
	this->ProductionSpeed_Text->SetText(text);
}

void UBuildingUserWidget::SetElapsedProductionTime(float ElapsedProduction, float MaxProduction)
{
	if (this->ElapsedProduction_Bar == nullptr)
		return;


	this->ElapsedProduction_Bar->SetPercent(ElapsedProduction / MaxProduction);
}