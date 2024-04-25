#include "Actors/Weapon/Rifle.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActionComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystem.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Interface/CharacterInterface.h"

#include "Actors/Weapon/Attachment.h"

ARifle::ARifle()
{
	KeyValue = "Rifle";
	{
		ConstructorHelpers::FObjectFinder<UParticleSystem> Asset(TEXT("/Script/Engine.ParticleSystem'/Game/_dev/Particles_Rifle/Particles/VFX_Muzzleflash.VFX_Muzzleflash'"));
		if (Asset.Succeeded())
			FlashParticle = Asset.Object;
	}
	{
		ConstructorHelpers::FObjectFinder<UParticleSystem> Asset(TEXT("/Script/Engine.ParticleSystem'/Game/_dev/Particles_Rifle/Particles/VFX_Eject_bullet.VFX_Eject_bullet'"));
		if (Asset.Succeeded())
			EjectParticle = Asset.Object;
	}
	{
		ConstructorHelpers::FObjectFinder<UParticleSystem> Asset(TEXT("/Script/Engine.ParticleSystem'/Game/_dev/Particles_Rifle/Particles/VFX_Impact_Default.VFX_Impact_Default'"));
		if (Asset.Succeeded())
			ImpactParticle = Asset.Object;
	}
	{
		ConstructorHelpers::FObjectFinder<USoundBase> Asset(TEXT("/Script/Engine.SoundWave'/Game/Sounds/S_RifleShoot.S_RifleShoot'"));
		if (Asset.Succeeded())
			FireSoundCue = Asset.Object;
	}
	{
		ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> Asset(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/_dev/Materials/M_Decal_Inst.M_Decal_Inst'"));
		if (Asset.Succeeded())
			DecalMaterial = Asset.Object;
	}
	{

		ConstructorHelpers::FClassFinder<UCameraShakeBase> Asset(TEXT("/Script/Engine.Blueprint'/Game/_dev/CameraShake.CameraShake_C'"));
		if (Asset.Succeeded())
			CameraShakeClass = Asset.Class;
	}
}

void ARifle::BeginPlay()
{
	Super::BeginPlay();
}

void ARifle::Attack()
{
	ICharacterInterface* CharacterInterface = Cast<ICharacterInterface>(OwnerCharacter);
	if (CharacterInterface == nullptr) return;

	FVector strat, end, direction;
	CharacterInterface->GetAimInfo(strat, end, direction);

	APlayerController* controller = OwnerCharacter->GetController<APlayerController>();

	if (!!controller)
		controller->PlayerCameraManager->StartCameraShake(CameraShakeClass);
	
	USkeletalMeshComponent* Mesh = Attachment->GetComponentByClass<USkeletalMeshComponent>();

	FVector muzzleLocation = Mesh->GetSocketLocation("Muzzle");
	//if (!!BulletClass)
	//	GetWorld()->SpawnActor<ACBullet>(BulletClass, muzzleLocation, direction.Rotation());

	//Play Effect
	UGameplayStatics::SpawnEmitterAttached(FlashParticle, Mesh, "Muzzle", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	UGameplayStatics::SpawnEmitterAttached(EjectParticle, Mesh, "EjectBullet", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSoundCue, muzzleLocation);

	//Raising Pitch
	CurrentPitch -= 0.5f * GetWorld()->GetDeltaSeconds();
	OwnerCharacter->AddControllerPitchInput(CurrentPitch);

	//LineTarce
	FHitResult hitResult;
	FCollisionQueryParams collisionQueryParams;
	collisionQueryParams.AddIgnoredActor(this);
	collisionQueryParams.AddIgnoredActor(OwnerCharacter);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, strat, end, ECollisionChannel::ECC_Visibility, collisionQueryParams))
	{
		AStaticMeshActor* staticMeshActor = Cast<AStaticMeshActor>(hitResult.GetActor());
		if (!!staticMeshActor)
		{
			UStaticMeshComponent* staticMeshComp = Cast<UStaticMeshComponent>(staticMeshActor->GetRootComponent());
			if (!!staticMeshComp)
			{
				// Spanw Decal & Impact Particle
				FRotator decalRotator = hitResult.ImpactNormal.Rotation();
				UDecalComponent* decalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(5), hitResult.Location, decalRotator, 10.f);
				decalComp->SetFadeScreenSize(0);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, hitResult.Location, decalRotator, true);

			
			}
		}
	}

}

void ARifle::MouseR()
{
	Action->OnAim();
}

void ARifle::OffMouseR()
{
	Action->OffAim();
}
