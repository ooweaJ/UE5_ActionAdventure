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
#include "Characters/Controller/BossAIController.h"
#include "Actors/Weapon/BossProJectile.h"

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
	{
		ConstructorHelpers::FClassFinder<ABossProJectile> Class(TEXT("/Script/Engine.Blueprint'/Game/_dev/Actors/Weapon/BossSpawn.BossSpawn_C'"));
		if (Class.Succeeded())
			Projectile = Class.Class;
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

void ABossWeapon::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	//Effect
	UParticleSystem* hitEffect = PreData.Effect;
	if (!!hitEffect)
	{
		FTransform transform = PreData.EffectTransform;
		transform.AddToTranslation(InOtherCharacter->GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
	}

	FDamageEvent de;
	de.DamageTypeClass = PreData.DamageType;
	InOtherCharacter->TakeDamage(PreData.Power, de, InAttacker->GetController(), InCauser);

	if (!Cast<APlayerController>(InAttacker->GetController())) return;

	//Camera Shake
	TSubclassOf<UCameraShakeBase> shake = PreData.ShakeClass;
	if (!!shake)
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		controller->PlayerCameraManager->StartCameraShake(shake);
	}

}

void ABossWeapon::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{

}

void ABossWeapon::MouseL()
{
	// 보스기본 공격
	if (!State->IsIdleMode()) return;
	State->SetActionMode();

	TArray<FActionData> Datas = DefaultData->ActionDatas;
	int32 Random = FMath::RandRange(0, Datas.Num() - 1);

	bCombo = Datas[Random].bCanCombo;

	MontageData(Datas[Random]);
}

void ABossWeapon::MouseR()
{
	// 보스의 페이크 공격 2종류

	Boss->ClearFoucsTarget();

	if (FakeIndex == 0)
	{
		TArray<FActionData> Datas = FakeData->ActionDatas;
		int32 Random = FMath::RandRange(0, Datas.Num() - 1);

		bCombo = Datas[Random].bCanCombo;
		MontageData(Datas[Random]);
	}
	else
	{
		TArray<FActionData> Datas = Fake2Data->ActionDatas;
		int32 Random = FMath::RandRange(0, Datas.Num() - 1);

		bCombo = Datas[Random].bCanCombo;
		MontageData(Datas[Random]);
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

	MontageData(Datas[Random]);
}

void ABossWeapon::EndAction()
{
	Super::EndAction();
}

void ABossWeapon::Approach()
{
	if (State->IsActionMode() || State->IsHittedMode()) return;
	State->SetActionMode();

	TArray<FActionData> Datas = ApproachData->ActionDatas;
	int32 Random = FMath::RandRange(0, Datas.Num() - 1);

	MontageData(Datas[Random]);
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

	MontageData(Datas[Random]);
}

void ABossWeapon::RangeAttack()
{
	if (!State->IsIdleMode()) return;
	State->SetActionMode();


	TArray<FActionData> Datas = SkillData->ActionDatas;

	MontageData(Datas[0]);
}

void ABossWeapon::TargetDotAction()
{
	Boss->StopMontage(PreData.AnimMontage);
}

void ABossWeapon::StrafeAttack()
{
	FTransform Transform;
	FVector Location = OwnerCharacter->GetMesh()->GetSocketLocation("Sword_Tip");
	Transform.SetLocation(Location);
	ABossProJectile* Actor = OwnerCharacter->GetWorld()->SpawnActorDeferred<ABossProJectile>(Projectile, Transform, OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Actor->SetTarget(Boss->GetBossController()->GetTarget());
	Actor->FinishSpawning(Transform, true);
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
