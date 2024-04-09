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
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimYawRate = abs((GetControlRotation().Yaw - PreviousAimYaw) / DeltaTime);
	PreviousAimYaw = GetControlRotation().Yaw;

	if(GetVelocity().Size2D() >= 100.)
	LastVelocity = GetVelocity().Rotation();
	FRotator Target(0.0, LastVelocity.Yaw, 0.0);
	float a = 20.f; // 0~ 20 을 0~3값에따라 만들어지는 float 변수 달리는 모드를 생각하면됨
	float calculate = UKismetMathLibrary::MapRangeClamped(AimYawRate, 0.0, 300.0, 1.0, 3.0) * a;
	TargetRotation = UKismetMathLibrary::RInterpTo_Constant(TargetRotation, Target, DeltaTime, 500.f);
	SetActorRotation(UKismetMathLibrary::RInterpTo_Constant(GetActorRotation(), TargetRotation, DeltaTime, calculate));

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
	GetCharacterMovement()->MaxWalkSpeed = 900.f;
}

void ACPlayer::OffShift()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

}

