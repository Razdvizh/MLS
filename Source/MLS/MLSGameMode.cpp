// Copyright Epic Games, Inc. All Rights Reserved.

#include "MLSGameMode.h"
#include "MLSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMLSGameMode::AMLSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
