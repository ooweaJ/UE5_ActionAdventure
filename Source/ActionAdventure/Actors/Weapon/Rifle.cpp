#include "Actors/Weapon/Rifle.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystem.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Interface/CharacterInterface.h"
#include "Engine.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Actors/Weapon/Attachment.h"
#include "Components/ActionComponent.h"
#include "Components/StateComponent.h"
#include "Characters/Players/CPlayer.h"
#include "Characters/AI/AICharacter.h"

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

		ConstructorHelpers::FClassFinder<UCameraShakeBase> Asset(TEXT("/Script/Engine.Blueprint'/Game/_dev/RifleShake.RifleShake_C'"));
		if (Asset.Succeeded())
			CameraShakeClass = Asset.Class;
	}
	{
		ConstructorHelpers::FClassFinder<AActor> Asset(TEXT("/Script/Engine.Blueprint'/Game/_dev/Actors/Bullet.Bullet_C'"));
		if (Asset.Succeeded())
			Bullet = Asset.Class;
	}
}

void ARifle::BeginPlay()
{
	Super::BeginPlay();
	if (AAICharacter* aipawn = Cast<AAICharacter>(OwnerCharacter))
		aipawn->SetAttackRange(1000.f);
}

void ARifle::MouseL()
{
	if (Cast<AAICharacter>(OwnerCharacter))
		Action->OnAim();
	if (!Action->IsAiming()) return;
	if (bFiring == true) return;

	bFiring = true;

	ICharacterInterface* CharacterInterface = Cast<ICharacterInterface>(OwnerCharacter);
	if (CharacterInterface == nullptr) return;

	FVector start, end, direction;
	CharacterInterface->GetAimInfo(start, end, direction);
	
	Mesh = Attachment->GetComponentByClass<USkeletalMeshComponent>();
	FVector muzzleLocation = Mesh->GetSocketLocation("Muzzle");

	
	GetWorld()->SpawnActor<AActor>(Bullet, muzzleLocation, direction.Rotation());

	//Play Effect
	UGameplayStatics::SpawnEmitterAttached(FlashParticle, Mesh, "Muzzle", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSoundCue, muzzleLocation);

	if (Cast<AAICharacter>(OwnerCharacter))
		AIfire(start,end);
	else
		fire(start, end);
}



void ARifle::MouseR()
{
	Super::MouseR();

	Action->OnAim();
	State->SetOffOrient();
	if (ACPlayer* player = Cast<ACPlayer>(OwnerCharacter))
		player->OnAim();
}

void ARifle::OffMouseR()
{
	Super::OffMouseR();

	Action->OffAim();
	State->SetOnOrient();
	if (ACPlayer* player = Cast<ACPlayer>(OwnerCharacter))
		player->OffAim();
}

void ARifle::BeginAction()
{
	Super::BeginPlay();
}

void ARifle::EndAction()
{
	Super::EndAction();

	bFiring = false;
}

void ARifle::EndActionAI()
{
	State->SetIdleMode();
	bFiring = false;
}

void ARifle::fire(FVector start, FVector end)
{
	APlayerController* controller = OwnerCharacter->GetController<APlayerController>();

	if (!!controller)
		controller->PlayerCameraManager->StartCameraShake(CameraShakeClass);

	UGameplayStatics::SpawnEmitterAttached(EjectParticle, Mesh, "EjectBullet", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);

	FHitResult hitResult;

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	objectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ignore;
	ignore.Add(OwnerCharacter);

	TArray<FActionData> Datas = DefaultData->ActionDatas;
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);

	UKismetSystemLibrary::K2_SetTimer(this, "EndAction", 0.15f, false);
	if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), start, end, objectTypes, true, ignore, EDrawDebugTrace::None, hitResult, true))
	{
		ACharacter* character = Cast<ACharacter>(hitResult.GetActor());
		if (!!character)
		{
			UParticleSystem* hitEffect = Datas[0].Effect;
			if (!!hitEffect)
			{
				FTransform transform = Datas[0].EffectTransform;
				transform.AddToTranslation(hitResult.Location);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
			}
			FDamageEvent de;
			de.DamageTypeClass = Datas[0].DamageType;
			character->TakeDamage(Datas[0].Power, de, OwnerCharacter->GetController(), this);
			return;
		}
		{
			FRotator decalRotator = hitResult.ImpactNormal.Rotation();
			UDecalComponent* decalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(5), hitResult.Location, decalRotator, 10.f);
			decalComp->SetFadeScreenSize(0);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, hitResult.Location, decalRotator, true);
		}
	}

	OwnerCharacter->AddControllerPitchInput(CurrentPitch);
}

void ARifle::AIfire(FVector start, FVector end)
{

	FHitResult hitResult;

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	objectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ignore;
	ignore.Add(OwnerCharacter);

	TArray<FActionData> Datas = DefaultData->ActionDatas;
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);

	UKismetSystemLibrary::K2_SetTimer(this, "EndActionAI", 0.3f, false);
	if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), start, end, objectTypes, true, ignore, EDrawDebugTrace::ForDuration, hitResult, true))
	{
		ACharacter* character = Cast<ACharacter>(hitResult.GetActor());
		if (!!character)
		{
			UParticleSystem* hitEffect = Datas[0].Effect;
			if (!!hitEffect)
			{
				FTransform transform = Datas[0].EffectTransform;
				transform.AddToTranslation(hitResult.Location);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
			}
			FDamageEvent de;
			de.DamageTypeClass = Datas[0].DamageType;
			character->TakeDamage(Datas[0].Power, de, OwnerCharacter->GetController(), this);
			return;
		}
		{
			FRotator decalRotator = hitResult.ImpactNormal.Rotation();
			UDecalComponent* decalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(5), hitResult.Location, decalRotator, 10.f);
			decalComp->SetFadeScreenSize(0);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, hitResult.Location, decalRotator, true);
		}
	}
}
