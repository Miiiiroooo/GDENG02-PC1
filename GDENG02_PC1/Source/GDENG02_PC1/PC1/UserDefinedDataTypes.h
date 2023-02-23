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
	Unknown          UMETA(DisplayName = "Unknown"),
	Iron             UMETA(DisplayName = "Iron"),
	Coal             UMETA(DisplayName = "Coal"),
	Steel_Beam       UMETA(DisplayName = "Steel Beam"),
	Lumber           UMETA(DisplayName = "Lumber"),
	Sewing_Machine   UMETA(DisplayName = "Sewing Machine")
};

UENUM()
enum class EBuildingStates : uint8
{
	Unknown          UMETA(DisplayName = "Unknown"),
	Producing        UMETA(DisplayName = "Producing"),
	Waiting          UMETA(DisplayName = "Waiting"),
	Exporting        UMETA(DisplayName = "Exporting")
};

UENUM()
enum class EVehicleStates : uint8
{
	Unknown          UMETA(DisplayName = "Unknown"),
	Idle             UMETA(DisplayName = "Idle"),
	Loading          UMETA(DisplayName = "Loading"),
	Delivering       UMETA(DisplayName = "Delivering"),
	Unloading        UMETA(DisplayName = "Unloading")
};

#pragma endregion ENUMS




#pragma region STRUCTS


#pragma endregion STRUCTS