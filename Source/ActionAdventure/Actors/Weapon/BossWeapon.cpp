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

	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> Asset(TEXT("/Script/Engine.AnimMontage'/Game/_dev/Characters/Boss/Animation/MotionFake/ready/Ready_Montage.Ready_Montage'"));
		if (Asset.Succeeded())
			Fake = Asset.Object;
	}
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> Asset(TEXT("/Script/Engine.AnimMontage'/Game/_dev/Characters/Boss/Animation/MotionFake/ready2/Ready2_Montage.Ready2_Montage'"));
		if (Asset.Succeeded())
			Fake2 = Asset.Object;
	}
}

void ABossWeapon::BeginPlay()
{
	Super::BeginPlay();
	{
		ApproachData = FindActionDataRow(TEXT("Approach"));
		SkillData = FindActionDataRow(TEXT("Skill"));
		ComboData = FindActionDataRow(TEXT("Finish"));
		MoveData = FindActionDataRow(TEXT("Move"));
		FakeData = FindActionDataRow(TEXT("Fake"));
		Fake2Data = FindActionDataRow(TEXT("Fake2"));
	}

	Boss = Cast<AAIBoss>(OwnerCharacter);
	Behavior = OwnerCharacter->GetController()->GetComponentByClass<UBossBehaviorComponent>();


}

void ABossWeapon::MouseL()
{
	if (!State->IsIdleMode()) return;
	State->SetActionMode();

	TArray<FActionData> Datas = DefaultData->ActionDatas;
	int32 Random = FMath::RandRange(0, Datas.Num() - 1);

	bCombo = Datas[Random].bCanCombo;
	Datas[Random].bCanMove ? Status->SetMove() : Status->SetStop();
	PreData = Datas[Random];
	OwnerCharacter->PlayAnimMontage(Datas[Random].AnimMontage, Datas[Random].PlayRate, Datas[Random].StartSection);
}

void ABossWeapon::MouseR()
{

	Boss->ClearFoucsTarget();
	if (FakeIndex == 0)
	{
		TArray<FActionData> Datas = FakeData->ActionDatas;
		int32 Random = FMath::RandRange(0, Datas.Num() - 1);
		bCombo = Datas[Random].bCanCombo;
		Datas[Random].bCanMove ? Status->SetMove() : Status->SetStop();
		OwnerCharacter->PlayAnimMontage(Datas[Random].AnimMontage, Datas[Random].PlayRate, Datas[Random].StartSection);
	}
	else
	{
		TArray<FActionData> Datas = Fake2Data->ActionDatas;
		int32 Random = FMath::RandRange(0, Datas.Num() - 1);
		bCombo = Datas[Random].bCanCombo;
		Datas[Random].bCanMove ? Status->SetMove() : Status->SetStop();
		OwnerCharacter->PlayAnimMontage(Datas[Random].AnimMontage, Datas[Random].PlayRate, Datas[Random].StartSection);
	}
}

void ABossWeapon::OffMouseR()
{
}

void ABossWeapon::BeginAction()
{
	if (!bCombo) return;
	if (Boss->GetDistanceToTarget() > 300.f) return;
	TArray<FActionData> Datas = ComboData->ActionDatas;

	int32 Random = FMath::RandRange(0, Datas.Num() - 1);
	Datas[Random].bCanMove ? Status->SetMove() : Status->SetStop();
	PreData = Datas[Random];
	OwnerCharacter->PlayAnimMontage(Datas[Random].AnimMontage, Datas[Random].PlayRate, Datas[Random].StartSection);
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
	if (!State->IsIdleMode()) return;
	State->SetActionMode();
	Boss->FoucsTarget();

	int RandomValue = FMath::RandRange(0, 1);
	int RandomValue2 = FMath::RandRange(0, 2);
	LoopMax = RandomValue2;

	if (RandomValue == 0)
	{
		PreLoop = Fake;
		FakeIndex = 0;
		OwnerCharacter->PlayAnimMontage(Fake);
	}
	else
	{
		PreLoop = Fake2;
		FakeIndex = 1;
		OwnerCharacter->PlayAnimMontage(Fake2);
	}
}

void ABossWeapon::MoveAttack()
{
	if (State->IsActionMode() || State->IsHittedMode()) return;
	State->SetActionMode();


	TArray<FActionData> Datas = MoveData->ActionDatas;

	int32 Random = FMath::RandRange(0, Datas.Num() - 1);

	OwnerCharacter->PlayAnimMontage(Datas[Random].AnimMontage, Datas[Random].PlayRate, Datas[Random].StartSection);
	Datas[Random].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ABossWeapon::RangeAttack()
{
	if (!State->IsIdleMode()) return;
	State->SetActionMode();


	TArray<FActionData> Datas = SkillData->ActionDatas;

	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate);
}

void ABossWeapon::TargetDotAction()
{
	Boss->StopMontage(PreData.AnimMontage);
}

void ABossWeapon::StrafeAttack()
{
	
}

void ABossWeapon::LoopMotion()
{
	if (LoopIndex == LoopMax)
	{
		LoopPower = LoopIndex;
		LoopIndex = 0;
		return;
	}
	LoopIndex++;

	OwnerCharacter->StopAnimMontage();
	OwnerCharacter->PlayAnimMontage(PreLoop, 1.f, "Loop");
}
