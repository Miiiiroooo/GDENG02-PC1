// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UserDefinedDataTypes.h"
#include "BuildingActorComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnReadyToExportSignature, UBuildingActorComponent*); // REECONSIDER MULTICAST


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG02_PC1_API UBuildingActorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UBuildingActorComponent();


// METHODS
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() EBuildingTypes GetType();
	UFUNCTION() FVector GetLocation();

	UFUNCTION() void ImportMaterial(TArray<EMaterials>& Materials);
	UFUNCTION() void ExportMaterial(TArray<EMaterials>& Materials);
	UFUNCTION() bool CheckIfInputStorageIsFull(EMaterials material);

private:
	UFUNCTION() void AssignMaterialsToBuilding();
	UFUNCTION() void Produce();
	UFUNCTION() void CheckIfBuildingCanProduce();


// ATTRIBUTES
private:
	// Configurables
	UPROPERTY(EditAnywhere) FName BuildingName;
	UPROPERTY(EditAnywhere) EBuildingTypes BuildingType;

	UPROPERTY(EditAnywhere) uint32 InputLimit;
	UPROPERTY(EditAnywhere) uint32 OutputLimit;
	UPROPERTY(EditAnywhere) float ProductionSpeed;


	// Normal Buildings Attributes
	UPROPERTY(VisibleAnywhere) uint32 InputStorageCount1;
	UPROPERTY(VisibleAnywhere) uint32 InputStorageCount2;
	UPROPERTY(VisibleAnywhere) uint32 OutputStorageCount;

	UPROPERTY(VisibleAnywhere) bool bHasPendingMaterialForOutput;
	UPROPERTY(VisibleAnywhere) float ElapsedProduction;

	UPROPERTY(VisibleAnywhere) EBuildingStates BuildingState;
	UPROPERTY(VisibleAnywhere) EMaterials CraftingMaterial1;
	UPROPERTY(VisibleAnywhere) EMaterials CraftingMaterial2;
	UPROPERTY(VisibleAnywhere) EMaterials ProducedMaterial;


	// Delegate
	FOnReadyToExportSignature OnReadyToExportDelegate;
};
