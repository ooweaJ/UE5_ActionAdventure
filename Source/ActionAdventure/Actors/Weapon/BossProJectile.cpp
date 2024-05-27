#include "Actors/Weapon/BossProJectile.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine.h"
#include "Actors/Weapon/DamageType/WeaponDamageType.h"
#include "Engine/DamageEvents.h"

ABossProJectile::ABossProJectile()
{
	PrimaryActorTick.bCanEverTick = true;


	{
		Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
		SetRootComponent(Scene);
		Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
		ThrowParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Throw"));
		Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	}

	Sphere->SetupAttachment(Scene);
	ThrowParticle->SetupAttachment(Sphere);

	Projectile->InitialSpeed = 3000.f;
	Projectile->MaxSpeed = 3000.f;
	Projectile->ProjectileGravityScale = 0.f;
	Projectile->bSweepCollision = true;

}

void ABossProJectile::SetTarget(AActor* TargetActor)
{
	Target = TargetActor;
}

void ABossProJectile::BeginPlay()
{
	Super::BeginPlay();
	InitialLifeSpan = 10.f;

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
	{
		FVector NewVelocity = Projectile->Velocity.GetSafeNormal();
		FRotator NewRotation = NewVelocity.Rotation();
		SetActorRotation(NewRotation);
	}
	if (bReturnToTarget)
	{
		FVector LookDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation).Vector().GetSafeNormal();
		FVector ReDirection = UKismetMathLibrary::VInterpTo(Projectile->Velocity.GetSafeNormal(), LookDirection, DeltaTime, 3.f);

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
			FVector location = Char->GetActorLocation();
			FRotator Rotation = Projectile->Velocity.GetSafeNormal().Rotation();
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactParticle, location, Rotation);
			FDamageEvent DamageEvent;
			Char->TakeDamage(10.f, DamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
			Destroy();
		}
	}
}

