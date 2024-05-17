#include "Actors/Weapon/BossProJectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABossProJectile::ABossProJectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ThrowParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Throw"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	Sphere->SetupAttachment(Scene);
	ThrowParticle->SetupAttachment(Sphere);

	Projectile->InitialSpeed = 3000.f;
	Projectile->MaxSpeed = 3000.f;
	Projectile->ProjectileGravityScale = 0.f;
	Projectile->bSweepCollision = true;

	InitialLifeSpan = 10.f;
}

void ABossProJectile::SetTarget(AActor* TargetActor)
{
	Target = TargetActor;
}

void ABossProJectile::BeginPlay()
{
	Super::BeginPlay();

	if (Target)
	{
		FVector TargetLocation = Target->GetActorLocation();
		TargetDirection = (TargetLocation - GetActorLocation()).GetSafeNormal();
		Projectile->Velocity = TargetDirection * ProjectileSpeed;

		Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABossProJectile::OnComponentBeginOverlap);
	}
}

void ABossProJectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TargetLocation = Target->GetActorLocation();
	FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
	float dotValue = FVector::DotProduct(TargetDirection, Direction);
	float Distance = GetDistanceTo(Target);

	if (bReturnToTarget)
	{
	/*	if (dotValue > 0.9)
		{
			bReturnToTarget = false;
			Projectile->Velocity = TargetDirection * ProjectileSpeed;
		}*/

		FVector LookDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation).Vector().GetSafeNormal();
		FVector ReDirection = UKismetMathLibrary::VInterpTo(GetActorForwardVector(), LookDirection, DeltaTime, 0.1f);

		// 프로젝타일을 새로운 방향으로 이동합니다.
		Projectile->Velocity = ReDirection * ProjectileSpeed;
	}

	if (dotValue < -0.5f && Distance > 500.f)
	{
		bReturnToTarget = true;
	}

}

void ABossProJectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) return;

	if (ACharacter* Char = Cast<ACharacter>(OtherActor))
	{
		if (!!ImpactParticle)
		{
			FTransform transform = ImpactParticleTransform;
			transform.AddToTranslation(SweepResult.Location);
			transform.SetRotation(FQuat(SweepResult.ImpactNormal.Rotation()));
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, transform);
		}
	}

}

