// Copyright Epic Games, Inc. All Rights Reserved.

#include "GDENG02_PC1GameMode.h"
#include "GDENG02_PC1Character.h"
#include "UObject/ConstructorHelpers.h"

AGDENG02_PC1GameMode::AGDENG02_PC1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
