#include "Actors/Weapon/BossWeapon.h"
#include "GameFramework/Character.h"
#include "Engine.h"
#include "AIController.h"

#include "Actors/Weapon/Attachment.h"
#include "Components/ActionComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"
#include "Components/BossBehaviorComponent.h"
#include "Actors/Weapon/DamageType/WeaponDamageType.h"
#include "Characters/AI/AIBoss.h"

ABossWeapon::ABossWeapon()
{
	KeyValue = TEXT("Boss");
}

void ABossWeapon::BeginPlay()
{
	Super::BeginPlay();

	ApproachData = FindActionDataRow(TEXT("Approach"));
	Boss = Cast<AAIBoss>(OwnerCharacter);
	Behavior = OwnerCharacter->GetController()->GetComponentByClass<UBossBehaviorComponent>();

	// AddComboData
	{
		TArray<FActionData> Datas = DefaultData->ActionDatas;
		for (FActionData Data : Datas)
		{
			if (Data.bCanCombo == false)
			{
				ComboData.Add(Data);
			}
		}
	}
}

void ABossWeapon::MouseL()
{
	if (!State->IsIdleMode()) return;
	State->SetActionMode();

	TArray<FActionData> Datas = DefaultData->ActionDatas;
	int32 Random = FMath::RandRange(0, Datas.Num() - 1);

	bCombo = Datas[Random].bCanCombo;
	OwnerCharacter->PlayAnimMontage(Datas[Random].AnimMontage, Datas[Random].PlayRate, Datas[Random].StartSection);
	Datas[Random].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ABossWeapon::MouseR()
{
}

void ABossWeapon::OffMouseR()
{
}

void ABossWeapon::BeginAction()
{
	if (!bCombo) return;
	if (Boss->GetDistanceToTarget() > 400.f) return;

	ACharacter* Target = Behavior->GetTarget();
	FVector TargetLocation = Target->GetActorLocation();
	FVector SelfLocation = Boss->GetActorLocation();

	FVector TargetDirection = (TargetLocation - SelfLocation).GetSafeNormal();

	FVector ForwardDirection = Boss->GetActorForwardVector();

	// 전방 및 일정 각도 내의 방향을 검사합니다.
	float AngleThreshold = 35.0f; // 일정 각도
	float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TargetDirection, ForwardDirection)));
	if (Angle <= AngleThreshold)
	{
		int32 Random = FMath::RandRange(0, ComboData.Num() - 1);
		OwnerCharacter->PlayAnimMontage(ComboData[Random].AnimMontage, ComboData[Random].PlayRate, ComboData[Random].StartSection);
		ComboData[Random].bCanMove ? Status->SetMove() : Status->SetStop();
	}
	else
	{
		// 액터와 캐릭터 사이의 거리를 계산합니다.
		float DistanceToTarget = FVector::Distance(SelfLocation, TargetLocation);

		// 회전 각도를 계산합니다.
		float AngleToTarget = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(GetActorForwardVector(), TargetDirection)));

		// 보간 속도를 조정합니다. 회전 각도에 따라서 보간 속도가 변경됩니다.
		float MinInterpSpeed = 1.0f; // 최소 보간 속도
		float MaxInterpSpeed = 10.0f; // 최대 보간 속도
		float MaxAngle = 90.0f; // 최대 회전 각도
		float InterpSpeed = FMath::Lerp(MinInterpSpeed, MaxInterpSpeed, FMath::Clamp(AngleToTarget / MaxAngle, 0.0f, 1.0f));

		// 액터를 캐릭터를 향하도록 보간하여 회전합니다.
		FRotator LookAtRotation = FRotationMatrix::MakeFromX(TargetDirection).Rotator();
		FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), InterpSpeed);

		// 회전합니다.
		SetActorRotation(NewRotation);
		int32 Random = FMath::RandRange(0, ComboData.Num() - 1);
		OwnerCharacter->PlayAnimMontage(ComboData[Random].AnimMontage, ComboData[Random].PlayRate, ComboData[Random].StartSection);
		ComboData[Random].bCanMove ? Status->SetMove() : Status->SetStop();
	}
}

void ABossWeapon::EndAction()
{
	Super::EndAction();
	UBossBehaviorComponent* behavior = OwnerCharacter->GetController()->GetComponentByClass<UBossBehaviorComponent>();
}

void ABossWeapon::Approach()
{
	if (State->IsActionMode() || State->IsHittedMode()) return;
	State->SetActionMode();


	TArray<FActionData> Datas = ApproachData->ActionDatas;

	int32 Random = FMath::RandRange(0, Datas.Num() - 1);

	OwnerCharacter->PlayAnimMontage(Datas[Random].AnimMontage, Datas[Random].PlayRate, Datas[Random].StartSection);
	Datas[Random].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ABossWeapon::FakeAttack()
{
}

void ABossWeapon::RangeAttack()
{
	if (!State->IsIdleMode()) return;
	State->SetActionMode();


	TArray<FActionData> Datas = DefaultData->ActionDatas;

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}
