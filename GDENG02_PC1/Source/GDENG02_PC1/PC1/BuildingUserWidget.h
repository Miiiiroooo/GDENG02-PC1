// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UserDefinedDataTypes.h"
#include "Blueprint/UserWidget.h"
#include "BuildingUserWidget.generated.h"


UCLASS()
class GDENG02_PC1_API UBuildingUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
// METHODS
public:
	void SetBuildingName(FName BuildingName);
	void SetCraftingMaterial1(EMaterials Material);
	void SetCraftingMaterial2(EMaterials Material);
	void SetProducedMaterial(EMaterials Material);

	void SetInputStorage1Text(uint32 Count, uint32 Limit);
	void SetInputStorage2Text(uint32 Count, uint32 Limit);
	void SetOutputStorageText(uint32 Count, uint32 Limit);

	void SetProductionSpeed(float ProductionSpeed);
	void SetElapsedProductionTime(float ElapsedProduction);

// ATTRIBUTES
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* BuildingName_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* CraftingMaterial1_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* CraftingMaterial2_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* ProducedMaterial_Text;

	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* InputStorage1_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* InputStorage2_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* OutPutStorage_Text;

	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* ProductionSpeed_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UProgressBar* ElapsedProduction_Bar;
};
