#include "Characters/AI/AIBoss.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperSpriteComponent.h"

#include "Characters/CAnimInstance.h"
#include "Characters/Controller/BossAIController.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/MoveComponent.h"
#include "Components/EquipComponent.h"
#include "Components/MontagesComponent.h"
#include "Engine.h"

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
	BossController = Cast<ABossAIController>(GetController());
	
}

void AAIBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	StateComponent->SetActionMode();
	StatusComponent->SetStop();

	if (Distance > 900.f)
	{
		bRangeAttack = false;
		RangeCoolTime = MaxRangeCoolTime;
	}
	else if (300.f < Distance && Distance < 900.f)
	{
		
	}
	else
	{
		
	}
}

float AAIBoss::GetDistanceToTarget()
{
	ACharacter* Target = BossController->GetTarget();
	float Distance = GetDistanceTo(Target);
	return Distance;
}

