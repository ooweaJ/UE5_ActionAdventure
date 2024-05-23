#include "Characters/Players/CPlayer.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Characters/CAnimInstance.h"
#include "Characters/AI/AIBoss.h"
#include "Characters/Controller/CPlayerController.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/MoveComponent.h"
#include "Components/EquipComponent.h"
#include "Components/MontagesComponent.h"

#include "Actors/Weapon/Weapon.h"
#include "Actors/Weapon/Attachment.h"
#include "SubSystem/DataSubsystem.h"
#include "UI/UI_UserStatus.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	{
		USkeletalMeshComponent* mesh = GetMesh();
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_manuel_rigged_001_ue4/rp_manuel_rigged_001_ue4.rp_manuel_rigged_001_ue4'"));
		if (!Asset.Succeeded()) return;

		mesh->SetSkeletalMesh(Asset.Object);
		mesh->SetRelativeLocation(FVector(0, 0, -88));
		mesh->SetRelativeRotation(FRotator(0, -90, 0));
	}

	// Create ActorComponents
	{
		StatusComponent = CreateDefaultSubobject<UStatusComponent>("StatusComponent");
		StateComponent = CreateDefaultSubobject<UStateComponent>("StateComponent");
		MoveComponent = CreateDefaultSubobject<UMoveComponent>("MoveComponent");
		ActionComponent = CreateDefaultSubobject<UActionComponent>("ActionComponent");
		EquipComponent = CreateDefaultSubobject<UEquipComponent>("EquipComponent");
		PaperComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Paper");
		MontagesComponent = CreateDefaultSubobject<UMontagesComponent>("MontagesComponent");
	}


	PaperComponent->SetupAttachment(RootComponent);
	PaperComponent->SetRelativeLocation(FVector(0., 0., 240.));
	PaperComponent->SetRelativeRotation(FRotator(0., 90.0, -90.0));
	PaperComponent->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	PaperComponent->bVisibleInSceneCaptureOnly = true;

	{
		static ConstructorHelpers::FObjectFinder<UPaperSprite> Asset(TEXT("/Script/Paper2D.PaperSprite'/Game/_dev/Characters/Players/Player_Sprite.Player_Sprite'"));
		if (!Asset.Succeeded()) return;
		PaperComponent->SetSprite(Asset.Object);
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	SpringArm->SetRelativeLocation(FVector(0, 0, 90));
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bDoCollisionTest = true;
	SpringArm->bUsePawnControlRotation = true;
	
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	ACPlayerController* Playercon = Cast<ACPlayerController>(GetController());
	if (Playercon)
	{
		UserStatus = Playercon->MainWidget->GetPlayerStatus();
		UserStatus->SetHP(StatusComponent->GetHealth(), StatusComponent->GetMaxHealth());
	}
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TargetActor)
	{
		FocusTarget();
	}
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
	}
}

float ACPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());

	StatusComponent->DecreaseHealth(Damage);
	UserStatus->SetHP(StatusComponent->GetHealth(), StatusComponent->GetMaxHealth());

	if (StatusComponent->GetHealth() <= 0.f)
	{
		StateComponent->SetDeadMode();
		Dead();
		return Damage;
	}

	Hitted(DamageEvent.DamageTypeClass);

	return Damage;
}

void ACPlayer::GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDriection)
{
	OutAimDriection = Camera->GetForwardVector();

	FTransform transform = Camera->GetComponentToWorld();
	FVector cameraLocation = transform.GetLocation();
	OutAimStart = cameraLocation + OutAimDriection * SpringArm->TargetArmLength;

	FVector recoilCone = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(OutAimDriection, 0.2f);

	OutAimEnd = cameraLocation + recoilCone * 10000;
}

void ACPlayer::OffFlying()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ACPlayer::OnShift()
{
	GetCharacterMovement()->MaxWalkSpeed = StatusComponent->GetRunSpeed();
}

void ACPlayer::OffShift()
{
	GetCharacterMovement()->MaxWalkSpeed = StatusComponent->GetWalkSpeed();
}

void ACPlayer::OnMouseL()
{
	ActionComponent->MouseL();
}

void ACPlayer::OnMouseR()
{
	ActionComponent->MouseR();
}

void ACPlayer::OffMouseR()
{
	ActionComponent->OffMouseR();
}

void ACPlayer::OnNum1()
{
	ActionComponent->Num1();
}

void ACPlayer::OnNum2()
{
	ActionComponent->Num2();

}

void ACPlayer::OnNum3()
{
	ActionComponent->Num3();
}

void ACPlayer::Parkour()
{

}

void ACPlayer::OnT()
{
	if (TargetActor)
	{
		(Cast<AAIBoss>(TargetActor))->OffTarget();
		TargetActor = nullptr;
		return;
	}

	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation;

	TArray<FHitResult> HitResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(5000.f);

	// 스피어 트레이스 수행
	bool bIsHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		ECC_Pawn, // Pawn 채널에서 탐색
		Sphere
	);

	if (bIsHit)
	{
		for (auto& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor && HitActor->IsA(AAIBoss::StaticClass()))
			{
				TargetActor = HitActor;
			}
		}
	}
}


void ACPlayer::OnAim()
{
	SpringArm->TargetArmLength = 0.f;
	Camera->FieldOfView = 60.f;
	Camera->SetRelativeLocation(FVector(20, 0, -20));
}

void ACPlayer::OffAim()
{
	SpringArm->TargetArmLength = 300.f;
	Camera->FieldOfView = 90.f;
	Camera->SetRelativeLocation(FVector(-20, 0, 20));
}

bool ACPlayer::IsComBat()
{
	return EquipComponent->HasWeapon();
}

void ACPlayer::SetDefault()
{
	Interaction = EInteraction::Default;
}

void ACPlayer::SetStore()
{
	Interaction = EInteraction::Store;
}

void ACPlayer::OnRoll()
{
	if (!StateComponent->IsIdleMode()) return;

	FVector Velocity = GetVelocity(); 

	if (!Velocity.IsNearlyZero()) 
	{
		FRotator TargetRotation = Velocity.Rotation(); 
		SetActorRotation(TargetRotation); 
	}
	MontagesComponent->PlayRoll();
}

void ACPlayer::BossSkill_Implementation()
{
	DetachWeapon();
}

void ACPlayer::BossSkillEnd_Implementation()
{
}

void ACPlayer::DetachWeapon()
{
	AItem* Item = EquipComponent->GetCurrentItem();
	Item->Attachment->OnDetach();
	Item->Attachment->DetachRootComponentFromParent();
}

void ACPlayer::FocusTarget()
{
	FVector Location = Camera->GetComponentLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(Location, TargetLocation);

	FQuat TargetQuat = TargetRotation.Quaternion();
	FRotator NewRotation = TargetQuat.Rotator();

	(Cast<AAIBoss>(TargetActor))->OnTarget();

	GetController()->SetControlRotation(NewRotation);
}
