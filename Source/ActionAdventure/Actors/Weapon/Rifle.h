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
	virtual void MouseL();
	virtual void MouseR();
	virtual void OffMouseR();
	virtual void BeginAction() override;
	UFUNCTION()
	virtual void EndAction() override;
	UFUNCTION()
	void EndActionAI();
	

	void fire(FVector start, FVector end);
	void AIfire(FVector start, FVector end);
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

	USkeletalMeshComponent* Mesh;
};
