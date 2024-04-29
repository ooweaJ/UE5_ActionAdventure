#pragma once

#include "CoreMinimal.h"
#include "Actors/Item.h"
#include "Engine/DamageEvents.h"
#include "Weapon.generated.h"

UCLASS()
class ACTIONADVENTURE_API AWeapon : public AItem
{
	GENERATED_BODY()
	
public:	
	AWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
