// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


class GDENG02_PC1_API UserDefinedDataTypes
{
public:
	UserDefinedDataTypes();
	~UserDefinedDataTypes();
};


#pragma region ENUMS

UENUM()
enum class EMaterials : uint8
{
	Unknown				     UMETA(DisplayName = "Unknown"),
	None				     UMETA(DisplayName = "None"),
	Iron					 UMETA(DisplayName = "Iron"),
	Coal					 UMETA(DisplayName = "Coal"),
	Steel_Beam			     UMETA(DisplayName = "Steel Beam"),
	Lumber				     UMETA(DisplayName = "Lumber"),
	Sewing_Machine			 UMETA(DisplayName = "Sewing Machine")
};

UENUM()
enum class EBuildingTypes : uint8
{
	Unknown					 UMETA(DisplayName = "Unknown"),
	Iron_Mine                UMETA(DisplayName = "Iron Mine"),
	Coal_Mine                UMETA(DisplayName = "Coal Mine"),
	Furnace                  UMETA(DisplayName = "Furnace"),
	Lumberjack_Hut           UMETA(DisplayName = "Lumberjack Hut"),
	Sewing_Machine_Factory   UMETA(DisplayName = "Sewing Machine Factory")
};

UENUM()
enum class EBuildingStates : uint8
{
	Unknown					 UMETA(DisplayName = "Unknown"),
	Producing				 UMETA(DisplayName = "Producing"),
	Waiting				   	 UMETA(DisplayName = "Waiting")
};

UENUM()
enum class EVehicleStates : uint8
{
	Unknown				    UMETA(DisplayName = "Unknown"),
	Idle				    UMETA(DisplayName = "Idle"),
	Fetching				UMETA(DisplayName = "Fetching"),
	Loading				    UMETA(DisplayName = "Loading"),
	Delivering              UMETA(DisplayName = "Delivering"),
	Unloading               UMETA(DisplayName = "Unloading")
};

UENUM()
enum class EDoorStates : uint8
{
	Unknown				    UMETA(DisplayName = "Unknown"),
	Open 					UMETA(DisplayName = "Open"),
	Closed					UMETA(DisplayName = "Closed"),
};

#pragma endregion ENUMS




#pragma region STRUCTS


#pragma endregion STRUCTS