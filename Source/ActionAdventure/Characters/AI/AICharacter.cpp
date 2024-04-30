#include "Characters/AI/AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine.h"
#include "Engine/DamageEvents.h"

#include "Characters/CAnimInstance.h"
#include "Characters/Controller/CAIController.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/MoveComponent.h"
#include "Components/EquipComponent.h"
#include "Components/MontagesComponent.h"
#include "Actors/Weapon/DamageType/WeaponDamageType.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

AAICharacter::AAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_carla_rigged_001_ue4/rp_carla_rigged_001_ue4.rp_carla_rigged_001_ue4'"));
		if (!Asset.Succeeded()) return;
		Meshs.Add(Asset.Object);
	}
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_claudia_rigged_002_ue4/rp_claudia_rigged_002_ue4.rp_claudia_rigged_002_ue4'"));
		if (!Asset.Succeeded()) return;
		Meshs.Add(Asset.Object);
	}
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_eric_rigged_001_ue4/rp_eric_rigged_001_ue4.rp_eric_rigged_001_ue4'"));
		if (!Asset.Succeeded()) return;
		Meshs.Add(Asset.Object);
	}
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_nathan_rigged_003_ue4/rp_nathan_rigged_003_ue4.rp_nathan_rigged_003_ue4'"));
		if (!Asset.Succeeded()) return;
		Meshs.Add(Asset.Object);
	}
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_sophia_rigged_003_ue4/rp_sophia_rigged_003_ue4.rp_sophia_rigged_003_ue4'"));
		if (!Asset.Succeeded()) return;
		Meshs.Add(Asset.Object);
	}
	{
		USkeletalMeshComponent* mesh = GetMesh();
		mesh->SetRelativeLocation(FVector(0, 0, -88));
		mesh->SetRelativeRotation(FRotator(0, -90, 0));

		int32 Random = FMath::RandRange(0, Meshs.Num() - 1);
		mesh->SetSkeletalMesh(Meshs[Random]);
		ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset{ TEXT("/Script/Engine.AnimBlueprint'/Game/_dev/Characters/Players/ABP_AI.ABP_AI_C'") };
		check(AnimAsset.Class);
		mesh->SetAnimInstanceClass(AnimAsset.Class);
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

	{
		static ConstructorHelpers::FObjectFinder<UPaperSprite> Asset(TEXT("/Script/Paper2D.PaperSprite'/Game/_dev/Texture/Enemy_Sprite.Enemy_Sprite'"));
		if (!Asset.Succeeded()) return;
		PaperComponent->SetSprite(Asset.Object);
	}

	PaperComponent->SetupAttachment(RootComponent);
	PaperComponent->SetRelativeLocation(FVector(0., 0., 240.));
	PaperComponent->SetRelativeRotation(FRotator(0., 90.0, -90.0));
	PaperComponent->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	PaperComponent->bVisibleInSceneCaptureOnly = true;

	AIControllerClass = ACAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	//EquipComponent->SelectWeapon(0);
}

void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());

	StatusComponent->DecreaseHealth(Damage);

	if (StatusComponent->GetHealth() <= 0.f)
	{
		StateComponent->SetDeadMode();
		Dead();
		return Damage;
	}
	
	Hitted(DamageEvent.DamageTypeClass);

	return Damage;
}

void AAICharacter::Dead()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->GlobalAnimRateScale = 0.f;
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	FVector start = GetActorLocation();
	FVector target = Attacker->GetActorLocation();
	FVector direction = start - target;
	direction.Normalize();

	GetMesh()->AddImpulse(direction * Damage * 1000);
	UKismetSystemLibrary::K2_SetTimer(this, "End_Dead", 2.f, false);
}

void AAICharacter::Hitted(TSubclassOf<UDamageType> Type)
{
	ACAIController* controller = Cast<ACAIController>(GetController());
	if (!!controller)
		controller->SetTargetKey(Attacker);
	
	if (!Type) return;
	UWeaponDamageType* type = Cast<UWeaponDamageType>(Type->GetDefaultObject());
	if (!type) return;
	switch (type->Type)
	{
	case EWeaponDamageType::Default:
		break;
	case EWeaponDamageType::Stiffness:
		break;
	case EWeaponDamageType::KnockBack:
	{
		MontagesComponent->PlayKnockBack();
		break;
	}
	default:
		break;
	}
}

void AAICharacter::End_Dead()
{
	ActionComponent->EndDead();
	Destroy();
}

