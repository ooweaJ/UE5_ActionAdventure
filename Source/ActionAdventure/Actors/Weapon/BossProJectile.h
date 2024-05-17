#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossProJectile.generated.h"

UCLASS()
class ACTIONADVENTURE_API ABossProJectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ABossProJectile();

	void SetTarget(AActor* TargetActor);
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly)
	FTransform ImpactParticleTransform;

private:
	UPROPERTY(VisibleDefaultsOnly)
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ThrowParticle;

	UPROPERTY(VisibleDefaultsOnly)
	class UProjectileMovementComponent* Projectile;

	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* Scene;
private:
	UPROPERTY(EditAnywhere)
	float ProjectileSpeed = 1500.f;

	UPROPERTY(EditAnywhere)
	float MaxDistance = 500.f;

	FVector TargetDirection;
	AActor* Target;
	bool bHasReachedTarget;
	bool bReturnToTarget;
};
