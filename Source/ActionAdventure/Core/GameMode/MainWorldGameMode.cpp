#include "Core/GameMode/MainWorldGameMode.h"
#include "Characters/Players/CPlayer.h"
#include "Characters/Controller/CPlayerController.h"

AMainWorldGameMode::AMainWorldGameMode()
{
	{
		ConstructorHelpers::FClassFinder<ACPlayer> Class(TEXT("/Script/Engine.Blueprint'/Game/_dev/Characters/Players/BP_Player.BP_Player_C'"));
		if (Class.Succeeded())
			PawnClass = Class.Class;
	}

	{
		ConstructorHelpers::FClassFinder<ACPlayerController> Class(TEXT("/Script/Engine.Blueprint'/Game/_dev/Characters/Players/BP_CPlayerController.BP_CPlayerController_C'"));
		if (Class.Succeeded())
			PlayConClass = Class.Class;
	}

	DefaultPawnClass = PawnClass;
	PlayerControllerClass = PlayConClass;
}
