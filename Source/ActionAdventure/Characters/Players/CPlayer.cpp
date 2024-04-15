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

#include "Characters/CAnimInstance.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/MoveComponent.h"

#include "Actors/Weapon/Weapon.h"
#include "SubSystem/DataSubsystem.h"

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
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_manuel_rigged_001_ue4/rp_manuel_rigged_001_ue4.rp_manuel_rigged_001_ue4'"));
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
	}

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	UDataSubsystem* DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	AWeapon* weapon = GetWorld()->SpawnActorDeferred<AWeapon>(AWeapon::StaticClass(), GetActorTransform(), this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	weapon->SetWeaponData(this, DataSubsystem->FindActionData(TEXT("NewRow")));
	weapon->FinishSpawning(GetActorTransform(), true);
	Weapon = weapon;
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
	}
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
	Weapon->Attack();
}

