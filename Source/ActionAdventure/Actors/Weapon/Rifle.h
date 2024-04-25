// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapon/Weapon.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONADVENTURE_API ARifle : public AWeapon
{
	GENERATED_BODY()
public:
	ARifle();

protected:
	virtual void BeginPlay();
public:
	virtual void Attack();
	virtual void MouseR();
	virtual void OffMouseR();

};
