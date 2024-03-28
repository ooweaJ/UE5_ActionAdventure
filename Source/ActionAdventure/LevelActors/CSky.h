#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CSky.generated.h"

UCLASS()
class ACTIONADVENTURE_API ACSky : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetDefaultSky();

	UFUNCTION(BlueprintImplementableEvent)
	void SetNightSky();
};
