// Copyright Epic Games, Inc. All Rights Reserved.

#include "RTU_MPGameMode.h"
#include "RTU_MPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARTU_MPGameMode::ARTU_MPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
