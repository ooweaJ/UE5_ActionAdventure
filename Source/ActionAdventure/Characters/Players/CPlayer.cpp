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
	RotationInterpSpeed = 10.0f;
	MinWalkSpeed = 300.f;
	MaxWalkSpeed = 1000.f;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateTowardsMovementDirection(DeltaTime);

	FVector Forward = UKismetMathLibrary::LessLess_VectorRotator(GetVelocity(), GetActorRotation());
	Forward = Forward / 350.0f;
	LeanAxis = FMath::FInterpTo(LeanAxis, Forward.Y, DeltaTime, 4.f);
	UE_LOG(LogTemp, Warning, TEXT("%f"), LeanAxis);
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
	}
}

void ACPlayer::RotateTowardsMovementDirection(float DeltaTime)
{
	FVector MovementDirection = GetVelocity();

	if (!MovementDirection.IsNearlyZero())
	{
		FRotator DesiredRotation = MovementDirection.Rotation();
		TargetRotation = FMath::RInterpTo(TargetRotation, DesiredRotation, DeltaTime, RotationInterpSpeed );
		SetActorRotation(TargetRotation);
	}
}

void ACPlayer::OnShift()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

void ACPlayer::OffShift()
{
	GetCharacterMovement()->MaxWalkSpeed = MinWalkSpeed;

}

