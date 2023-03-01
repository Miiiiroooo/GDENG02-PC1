// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UserDefinedDataTypes.h"
#include "Blueprint/UserWidget.h"
#include "BuildingUserWidget.generated.h"


#ifndef LOCTEXT_NAMESPACE
#define LOCTEXT_NAMESPACE "DefaultLocTextNamespace"
#endif


UCLASS(Abstract, Blueprintable)
class GDENG02_PC1_API UBuildingUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
// METHODS
public:
	virtual void NativeConstruct() override;

	void SetBuildingName(FName BuildingName);
	void SetCraftingMaterial1(EMaterials Material);
	void SetCraftingMaterial2(EMaterials Material);
	void SetProducedMaterial(EMaterials Material);

	void SetInputStorage1Text(uint32 Count, uint32 Limit);
	void SetInputStorage2Text(uint32 Count, uint32 Limit);
	void SetOutputStorageText(uint32 Count, uint32 Limit);

	void SetBuildingState(EBuildingStates State);
	void SetProductionSpeed(float ProductionSpeed);
	void SetElapsedProductionTime(float ElapsedProduction, float MaxProduction);


// ATTRIBUTES
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* BuildingName_Text;
	UPROPERTY(VisibleAnywhere) EMaterials CraftingMaterial1;
	UPROPERTY(VisibleAnywhere) EMaterials CraftingMaterial2;
	UPROPERTY(VisibleAnywhere) EMaterials ProducedMaterial;

	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* InputStorage1_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* InputStorage2_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* OutputStorage_Text;

	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* BuildingState_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* ProductionSpeed_Text;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UProgressBar* ElapsedProduction_Bar;
};
