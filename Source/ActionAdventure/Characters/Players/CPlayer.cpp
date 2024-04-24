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
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

#include "Characters/CAnimInstance.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/MoveComponent.h"
#include "Components/EquipComponent.h"

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
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

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
	ActionComponent->MouseL();
}

void ACPlayer::OnNum1()
{
	ActionComponent->Num1();
}

void ACPlayer::OnNum2()
{
	ActionComponent->Num2();

}

