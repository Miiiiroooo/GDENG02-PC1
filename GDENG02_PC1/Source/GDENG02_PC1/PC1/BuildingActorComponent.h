// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UserDefinedDataTypes.h"
#include "BuildingActorComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnReadyToExportSignature, FVector);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG02_PC1_API UBuildingActorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UBuildingActorComponent();


// METHODS
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION() void Produce();
	UFUNCTION() void CheckIfBuildingCanProduce();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() void ImportMaterial(EMaterials material);
	UFUNCTION() void ExportMaterial();
	UFUNCTION() bool CheckIfInputStorageIsFull(EMaterials material);
	UFUNCTION() FVector GetBuildingPosition();


// ATTRIBUTES
private:
	// Configurables
	UPROPERTY(EditAnywhere) uint32 InputLimit;
	UPROPERTY(EditAnywhere) uint32 OutputLimit;
	UPROPERTY(EditAnywhere) float ProductionSpeed;

	UPROPERTY(EditAnywhere) EMaterials CraftingMaterial1;
	UPROPERTY(EditAnywhere) EMaterials CraftingMaterial2;


	// Normal Buildings Attributes
	UPROPERTY(VisibleAnywhere) uint32 InputStorageCount1;
	UPROPERTY(VisibleAnywhere) uint32 InputStorageCount2;
	UPROPERTY(VisibleAnywhere) uint32 OutputStorageCount;

	UPROPERTY(VisibleAnywhere) bool bHasPendingMaterialForOutput;
	UPROPERTY(VisibleAnywhere) float ElapsedProduction;

	UPROPERTY(VisibleAnywhere) EBuildingStates BuildingState;


	// Delegate
	FOnReadyToExportSignature OnReadyToExportDelegate;
};
