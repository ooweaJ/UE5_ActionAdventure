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
	virtual void BeginAction() override;
	UFUNCTION()
	virtual void EndAction() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "CameraShake")
	TSubclassOf<class UCameraShakeBase> CameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	class UParticleSystem* FlashParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	class UParticleSystem* EjectParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	class UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	class USoundBase* FireSoundCue;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	class UMaterialInstanceConstant* DecalMaterial;

	TSubclassOf<AActor> Bullet;
private:
	float CurrentPitch = -0.1f;
	bool bFiring;
};
