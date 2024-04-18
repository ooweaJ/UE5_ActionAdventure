#include "Actors/Weapon/Melee/MeleeWeapon.h"
#include "GameFramework/Character.h"
#include "Engine.h"

#include "Actors/Weapon/Attachment.h"
#include "Components/ActionComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"

void AMeleeWeapon::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InCauser, InOtherCharacter);
}

void AMeleeWeapon::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InCauser, InOtherCharacter);
}

void AMeleeWeapon::Attack()
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
}
