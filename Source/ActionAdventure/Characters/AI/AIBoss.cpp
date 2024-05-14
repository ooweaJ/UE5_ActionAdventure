#include "Characters/AI/AIBoss.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperSpriteComponent.h"
#include "Engine.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

#include "Characters/CAnimInstance.h"
#include "Characters/Controller/BossAIController.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/MoveComponent.h"
#include "Components/EquipComponent.h"
#include "Components/MontagesComponent.h"
#include "Components/BossBehaviorComponent.h"
#include "Actors/Weapon/BossWeapon.h"

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
		StatusComponent = CreateDefaultSubobject<UStatusComponent>("StatusComponent");
		StateComponent = CreateDefaultSubobject<UStateComponent>("StateComponent");
		MoveComponent = CreateDefaultSubobject<UMoveComponent>("MoveComponent");
		ActionComponent = CreateDefaultSubobject<UActionComponent>("ActionComponent");
		EquipComponent = CreateDefaultSubobject<UEquipComponent>("Equip");
		MontagesComponent = CreateDefaultSubobject<UMontagesComponent>("Montage");
		PaperComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Paper");
	}

	AIControllerClass = ABossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAIBoss::BeginPlay()
{
	Super::BeginPlay();
	{
		BossController = Cast<ABossAIController>(GetController());
		Behavior = BossController->GetComponentByClass<UBossBehaviorComponent>();
	}
	{
		EquipComponent->EquipItem(ABossWeapon::StaticClass());
		EquipComponent->SelectWeapon(0);
		Weapon = Cast<ABossWeapon>(EquipComponent->GetCurrentItem());
	}
}

void AAIBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

	if (StatusComponent->IsCanMove())
	{
		if (MovingDirection != FVector::ZeroVector)
		{
			AddMovementInput(MovingDirection);
		}
	}
}

void AAIBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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
	if (Distance > 900.f)
	{
		bRangeAttack = false;
		RangeCoolTime = MaxRangeCoolTime;
		Weapon->RangeAttack();
	}
	else if (300.f < Distance && Distance < 600.f)
	{
		float RandomValue = FMath::FRand();
		if (RandomValue < 0.45f)
		{
			Weapon->FakeAttack();
		}
		else if(RandomValue < 0.9f && RandomValue >= 0.45f)
		{
			Weapon->MoveAttack();
		}
		else
		{
			Weapon->MouseL();
		}
	}
	else
	{
		float RandomValue = FMath::FRand();
		if (RandomValue < 0.4f)
		{
			Weapon->MouseL();
		}
		else
		{
			Weapon->FakeAttack();
		}
	}
}

void AAIBoss::ApproachAction()
{
	Weapon->Approach();

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

void AAIBoss::RotateToTarget()
{
	FVector AILocation = GetActorLocation();

	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(AILocation, TargetLocation);
	FRotator CurrentRotation = GetActorRotation();

	FQuat CurrentQuat = CurrentRotation.Quaternion();
	FQuat TargetQuat = FRotator(CurrentRotation.Pitch, TargetRotation.Yaw, CurrentRotation.Roll).Quaternion();

	FQuat NewQuat = FMath::QInterpTo(CurrentQuat, TargetQuat, GetWorld()->GetDeltaSeconds(), 16.f);

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

