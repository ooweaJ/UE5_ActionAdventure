#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Road.generated.h"

UCLASS()
class ACTIONADVENTURE_API ARoad : public AActor
{
	GENERATED_BODY()
	
public:	
	ARoad();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
