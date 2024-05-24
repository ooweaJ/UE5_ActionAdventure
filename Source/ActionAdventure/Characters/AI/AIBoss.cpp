#include "Characters/AI/AIBoss.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperSpriteComponent.h"
#include "Engine.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"

#include "Characters/CAnimInstance.h"
#include "Characters/Controller/BossAIController.h"
#include "Characters/Controller/CPlayerController.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/MoveComponent.h"
#include "Components/EquipComponent.h"
#include "Components/MontagesComponent.h"
#include "Components/BossBehaviorComponent.h"
#include "Components/DissolveComponent.h"
#include "Actors/Weapon/BossWeapon.h"
#include "Actors/BossRange.h"
#include "UI/UI_UserStatus.h"
#include "UI/PlayerMainWidget.h"

AAIBoss::AAIBoss()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->SetWalkableFloorAngle(60.f);

	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Skins/GlacialEmpress/Meshes/Aurora_GlacialEmpress.Aurora_GlacialEmpress'"));
		if (Asset.Succeeded())
		{
			USkeletalMeshComponent* mesh = GetMesh();
			mesh->SetRelativeLocation(FVector(0, 0, -88));
			mesh->SetRelativeRotation(FRotator(0, -90, 0));
			mesh->SetSkeletalMesh(Asset.Object);
		}

	}
	{
		ConstructorHelpers::FClassFinder<ABossRange> Class(TEXT("/Script/Engine.Blueprint'/Game/_dev/Actors/Weapon/BP_AttackCircle.BP_AttackCircle_C'"));
		if (Class.Succeeded())
			RangeSpawn = Class.Class;
	}
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> Asset(TEXT("/Script/Engine.AnimMontage'/Game/ParagonAurora/Characters/Heroes/Aurora/Animations/Cast_Montage.Cast_Montage'"));
		if (Asset.Succeeded())
			CastMontage = Asset.Object;
	}
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> Asset(TEXT("/Script/Engine.AnimMontage'/Game/ParagonAurora/Characters/Heroes/Aurora/Animations/Emote_Slice_Montage.Emote_Slice_Montage'"));
		if (Asset.Succeeded())
			Page2Montage = Asset.Object;
	}

	{
		StatusComponent = CreateDefaultSubobject<UStatusComponent>("StatusComponent");
		StateComponent = CreateDefaultSubobject<UStateComponent>("StateComponent");
		MoveComponent = CreateDefaultSubobject<UMoveComponent>("MoveComponent");
		ActionComponent = CreateDefaultSubobject<UActionComponent>("ActionComponent");
		EquipComponent = CreateDefaultSubobject<UEquipComponent>("Equip");
		MontagesComponent = CreateDefaultSubobject<UMontagesComponent>("Montage");
		PaperComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Paper");
		TargetingWidget = CreateDefaultSubobject<UWidgetComponent>("Targeting");
		DissolveComponent = CreateDefaultSubobject<UDissolveComponent>("Dessolve");
	}

	TargetingWidget->SetupAttachment(RootComponent);
	AIControllerClass = ABossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAIBoss::BeginPlay()
{
	Super::BeginPlay();
	
	TargetingWidget->SetVisibility(false);
	{
		BossController = Cast<ABossAIController>(GetController());
		Behavior = BossController->GetComponentByClass<UBossBehaviorComponent>();
	}
	{
		EquipComponent->EquipItem(ABossWeapon::StaticClass());
		EquipComponent->SelectWeapon(0);
		Weapon = Cast<ABossWeapon>(EquipComponent->GetCurrentItem());
	}
	{
		ACPlayerController* playercon = Cast<ACPlayerController>(GetWorld()->GetFirstPlayerController());
		if (playercon)
		{
			MainWidget = playercon->MainWidget;
			BossHPBar = playercon->MainWidget->GetBossHPBar();
			BossSkillBar = playercon->MainWidget->GetBossSkillBar();
			BossHPBar->SetHP(StatusComponent->GetHealth(),StatusComponent->GetMaxHealth());
			BossHPBar->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AAIBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Page2)
	{
		if (bLastAttack == false)
		{

			LastAttackdCollTime += DeltaTime;
			BossSkillBar->SetHP(LastAttackdCollTime, MaxLastAttackCollTime);
			if (LastAttackdCollTime >= MaxLastAttackCollTime)
			{
				bLastAttack = true;
				LastAttack();
			}
		}
	}

	if (bTargetRotation)
	{
		TargetRotation();
	}

	if (!bRangeAttack)
	{
		RangeCoolTime -= DeltaTime;
		if (RangeCoolTime <= 0.f)
		{
			bRangeAttack = true;
			RangeCoolTime = 0.f;
		}
	}


	if (!bAvoid)
	{
		AvoidCollTime -= DeltaTime;
		if (AvoidCollTime <= 0.f)
		{
			bAvoid = true;
			AvoidCollTime = 0.f;
		}
	}

	if (StatusComponent->IsCanMove())
	{
		if (MovingDirection != FVector::ZeroVector)
		{
			AddMovementInput(MovingDirection);
		}
	}
}

float AAIBoss::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());

	StatusComponent->DecreaseHealth(Damage);
	BossHPBar->SetHP(StatusComponent->GetHealth(), StatusComponent->GetMaxHealth());

	if (StatusComponent->GetHealth() <= 0.f)
	{
		if (Page2)
		{
			StatusComponent->SetStop();
			StopAnimMontage();
			StateComponent->SetDeadMode();
			return Damage;
		}

		Page2 = true;
		Page2Start();
		StatusComponent->Set2Page();
		BossHPBar->SetHP(StatusComponent->GetHealth(), StatusComponent->GetMaxHealth());
		BossSkillBar->SetVisibility(ESlateVisibility::Visible);
		BossSkillBar->SetHP(LastAttackdCollTime, MaxLastAttackCollTime);
		return Damage;
	}

	return Damage;
}

void AAIBoss::SetMoveDirection(const FVector Direction)
{
	MovingDirection = Direction;
}

void AAIBoss::SetMoveDirection(const AActor* Actor)
{
	MovingDirection = (Actor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
}

void AAIBoss::DiceAction()
{
	float Distance = GetDistanceToTarget();

	if (Page2)
	{
		if (Distance > 900.f)
		{
			bRangeAttack = false;
			RangeCoolTime = MaxRangeCoolTime;
			Weapon->RangeAttack();
		}
		else if (300.f < Distance && Distance < 600.f)
		{
			float RandomValue = FMath::FRand();
			if (RandomValue < 6.5f)
			{
				Weapon->FakeAttack();
			}
			else
			{
				Weapon->MoveAttack();
			}
		}
		else
		{
			float RandomValue = FMath::FRand();
			if (RandomValue < 0.5f)
			{
				Weapon->MouseL();
			}
			else
			{
				Weapon->FakeAttack();
			}
		}
	}
	else
	{
		if (Distance > 300.f)
			Weapon->MoveAttack();
		else
			Weapon->MouseL();
	}
}

void AAIBoss::ApproachAction()
{
	Weapon->Approach();

}

void AAIBoss::Avoid()
{
	MontagesComponent->PlayBossAvoid();
}


void AAIBoss::AvoidTarget()
{
	ACharacter* Target = BossController->GetTarget();
	if (!Target) return;

	// 타겟 및 보스 위치 가져오기
	FVector TargetLocation2 = Target->GetActorLocation();
	FVector BossLocation = GetActorLocation();

	// 보스가 타겟으로부터 멀어지는 방향 계산
	FVector AvoidDirection = (BossLocation - TargetLocation2).GetSafeNormal();

	// 멀어지는 방향으로 500 유닛 떨어진 위치 계산
	FVector EndPos = BossLocation + (AvoidDirection * 600);

	// 발사 속도 계산
	FVector LaunchVelocity;
	bool bHaveValidSolution = UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), LaunchVelocity, BossLocation, EndPos, 0.f, 0.45f);

	if (bHaveValidSolution)
	{
		// 예측 경로 설정
		FPredictProjectilePathParams Params;
		Params.StartLocation = BossLocation;
		Params.LaunchVelocity = LaunchVelocity;
		Params.ProjectileRadius = 10.f;
		Params.MaxSimTime = 3.f;
		Params.bTraceWithCollision = true;
		Params.ActorsToIgnore.Add(this);
		Params.DrawDebugType = EDrawDebugTrace::None;

		// 예측 경로 결과
		FPredictProjectilePathResult Result;
		UGameplayStatics::PredictProjectilePath(GetWorld(), Params, Result);

		// 경로 데이터 저장
		TArray<FVector> PathPoints;
		for (const FPredictProjectilePathPointData& PointData : Result.PathData)
		{
			PathPoints.Add(PointData.Location);
	
		}

		// 타이머를 사용하여 보스의 위치를 업데이트
		if (PathPoints.Num() > 0)
		{
			GetWorldTimerManager().SetTimerForNextTick([this, PathPoints]() {
				MoveAlongPath(PathPoints, 0);
				});
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid solution for projectile velocity."));
	}
}

void AAIBoss::MoveAlongPath(TArray<FVector> PathPoints, int32 CurrentPointIndex)
{
	if (CurrentPointIndex < PathPoints.Num())
	{
		SetActorLocation(PathPoints[CurrentPointIndex], true);

		GetWorldTimerManager().SetTimerForNextTick([this, PathPoints, CurrentPointIndex]() {
			MoveAlongPath(PathPoints, CurrentPointIndex + 1);
			});
	}
}

void AAIBoss::StrafeAttack()
{
	if (!StateComponent->IsIdleMode()) return;
	if (StrafeAttackConunt == 0) return;
	--StrafeAttackConunt;
	StateComponent->SetActionMode();
	PlayAnimMontage(CastMontage);
}

void AAIBoss::RangeAttack()
{
	FTransform Transform;
	Transform.SetLocation(BossController->GetTarget()->GetActorLocation());

	FActorSpawnParameters param;
	param.Owner = this;
	param.Instigator = this;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ABossRange>(RangeSpawn, Transform, param);
}


void AAIBoss::Dead_Implementation()
{
}

void AAIBoss::DeadDissolve()
{
	DissolveComponent->Play();
}

float AAIBoss::GetDistanceToTarget()
{
	ACharacter* Target = BossController->GetTarget();
	float Distance = GetDistanceTo(Target);
	return Distance;
}

void AAIBoss::TargetRotation()
{
	ACharacter* Target = BossController->GetTarget();
	if (!Target) return;

	TargetLocation = Target->GetActorLocation();

	RotateToTarget();
}

void AAIBoss::FoucsTarget()
{
	ACharacter* Target = BossController->GetTarget();
	if (!Target) return;
	StateComponent->SetOffOrient();
	BossController->K2_SetFocus(Target);
}

void AAIBoss::ClearFoucsTarget()
{
	StateComponent->SetOnOrient();
	BossController->ClearFocus(EAIFocusPriority::Gameplay);
}

void AAIBoss::OnTarget()
{
	TargetingWidget->SetVisibility(true);
}

void AAIBoss::OffTarget()
{
	TargetingWidget->SetVisibility(false);
}

void AAIBoss::LastAttack_Implementation()
{
	StateComponent->SetActionMode();

	FVector Start = GetActorLocation();
	FVector SetPlayer = Start + (GetActorForwardVector() * 300.f);
	ACPlayer* CPlayer = Cast<ACPlayer>(BossController->GetTarget());
	if (CPlayer)
	{
		Player = CPlayer;
		CPlayer->SetActorLocation(SetPlayer);
		CPlayer->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(SetPlayer, Start));
		CPlayer->BossSkill();
	}
}

void AAIBoss::StopMontage(UAnimMontage* InMontage)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	//MovingDirection = FVector::ZeroVector;
	
	if (AnimInstance && InMontage)
	{
		AnimInstance->Montage_SetPlayRate(InMontage, 0.1f);

		// 델리게이트를 생성하여 ResumeMontage 함수를 호출하고 파라미터를 전달합니다.
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AAIBoss::ResumeMontage, InMontage);

		// 랜덤 딜레이 시간
		float DelayTime = FMath::FRand();

		// 타이머를 설정하여 ResumeMontage를 호출합니다.
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, DelayTime, false);
	}
}

void AAIBoss::ResumeMontage(UAnimMontage* InMontage)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && InMontage)
	{
		AnimInstance->Montage_SetPlayRate(InMontage, 1.f);

	}
}

void AAIBoss::Page2Start_Implementation()
{
	StateComponent->SetActionMode();
	StatusComponent->SetStop();
	PlayAnimMontage(Page2Montage);
}

void AAIBoss::OnMainWidget()
{
	MainWidget->SetVisibility(ESlateVisibility::Visible);
}

void AAIBoss::OffMainWidget()
{
	MainWidget->SetVisibility(ESlateVisibility::Hidden);
}

FRotator AAIBoss::GetTargetRotation()
{
	ACharacter* Target = BossController->GetTarget();
	if (!Target) return FRotator();

	FVector targetlocation = Target->GetActorLocation();
	FVector AILocation = GetActorLocation();

	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(AILocation, targetlocation);

	return TargetRotation;
}

ABossAIController* AAIBoss::GetBossController()
{
	return BossController;
}

void AAIBoss::RotateToTarget()
{
	FVector AILocation = GetActorLocation();

	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(AILocation, TargetLocation);
	FRotator CurrentRotation = GetActorRotation();

	FQuat CurrentQuat = CurrentRotation.Quaternion();
	FQuat TargetQuat = FRotator(CurrentRotation.Pitch, TargetRotation.Yaw, CurrentRotation.Roll).Quaternion();

	FQuat NewQuat = FMath::QInterpTo(CurrentQuat, TargetQuat, GetWorld()->GetDeltaSeconds(), 8.f);

	FRotator NewRotation = NewQuat.Rotator();
	SetActorRotation(NewRotation);
}

bool AAIBoss::IsTargetInFront()
{
	FVector AILocation = GetActorLocation();
	FVector DirectionToTarget = (TargetLocation - AILocation).GetSafeNormal();
	FVector AIForwardVector = GetActorForwardVector();

	float DotProduct = FVector::DotProduct(DirectionToTarget, AIForwardVector);
	
	return DotProduct > 0.9f;
}

