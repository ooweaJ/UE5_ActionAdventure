// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "WeaponDamageType.generated.h"

UENUM(BlueprintType)
enum class EWeaponDamageType : uint8
{
	Default, Stiffness, KnockBack, Max
};


UCLASS()
class ACTIONADVENTURE_API UWeaponDamageType : public UDamageType
{
	GENERATED_BODY()
	
public:
	EWeaponDamageType Type;
};
