#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Actors/Weapon/DamageType/WeaponDamageType.h"
#include "CharacterInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class ACTIONADVENTURE_API ICharacterInterface
{
	GENERATED_BODY()

public:
	virtual void Hitted(TSubclassOf<UDamageType> Type) = 0;
	virtual void Dead() = 0;
	virtual void End_Dead() = 0;
	virtual void GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDriection) {};
};
