#include "Actors/Weapon/Melee/MeleeWeapon.h"
#include "GameFramework/Character.h"
#include "Engine.h"
#include "AIController.h"

#include "Actors/Weapon/Attachment.h"
#include "Components/ActionComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"
#include "Actors/Weapon/DamageType/WeaponDamageType.h"

void AMeleeWeapon::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InCauser, InOtherCharacter);

	TArray<FActionData> Datas = DefaultData->ActionDatas;

	//Effect
	UParticleSystem* hitEffect = Datas[ComboCount].Effect;
	if (!!hitEffect)
	{
		FTransform transform = Datas[ComboCount].EffectTransform;
		transform.AddToTranslation(InOtherCharacter->GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
	}
	FDamageEvent de;
	de.DamageTypeClass = Datas[ComboCount].DamageType;
	//de.DamageTypeClass = UWeaponDamageType::StaticClass();
	InOtherCharacter->TakeDamage(Datas[ComboCount].Power, de, InAttacker->GetController(), InCauser);

	if (!Cast<APlayerController>(InAttacker->GetController())) return;

	//Camera Shake
	TSubclassOf<UCameraShakeBase> shake = Datas[ComboCount].ShakeClass;
	if (!!shake)
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		controller->PlayerCameraManager->StartCameraShake(shake);
	}

	//HitStop
	float hitStop = Datas[ComboCount].HitStop;
	if (FMath::IsNearlyZero(hitStop) == false)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.01f);
		UKismetSystemLibrary::K2_SetTimer(this, "RestoreGlobalTimeDilation", hitStop * 0.01f , false);
	}
}

void AMeleeWeapon::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InCauser, InOtherCharacter);
}

void AMeleeWeapon::MouseL()
{
	if (!(DefaultData->ActionDatas.Num() > 0)) return;

	if (bCanCombo == true)
	{
		bCanCombo = false;
		bSucceed = true;

		return;
	}

	if (!State->IsIdleMode()) return;
	State->SetActionMode();

	TArray<FActionData> Datas = DefaultData->ActionDatas;

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void AMeleeWeapon::BeginAction()
{
	if(!bSucceed) return;
	bSucceed = false;

	OwnerCharacter->StopAnimMontage();
	TArray<FActionData> Datas = DefaultData->ActionDatas;

	ComboCount++;
	ComboCount = FMath::Clamp(ComboCount, 0, Datas.Num() - 1);

	OwnerCharacter->PlayAnimMontage(Datas[ComboCount].AnimMontage, Datas[ComboCount].PlayRate, Datas[ComboCount].StartSection);
	Datas[ComboCount].bCanMove ? Status->SetMove() : Status->SetStop();
}

void AMeleeWeapon::EndAction()
{
	Super::EndAction();
	ComboCount = 0;
}

void AMeleeWeapon::RestoreGlobalTimeDilation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}