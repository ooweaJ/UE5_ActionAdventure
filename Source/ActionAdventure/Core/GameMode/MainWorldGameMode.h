#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainWorldGameMode.generated.h"

UCLASS()
class ACTIONADVENTURE_API AMainWorldGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMainWorldGameMode();

	FORCEINLINE bool IsMaxAI() { return MaxAI == CurrentAI; }
private:
	TSubclassOf<class ACPlayer> PawnClass;
	TSubclassOf<class ACPlayerController> PlayConClass;

	int32 MaxAI = 20;
	int32 CurrentAI = 0;
};
