#include "Characters/Controller/CPlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Characters/Players/CPlayer.h"

ACPlayerController::ACPlayerController()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/_dev/Characters/Players/Input/IMC_PlayerInput.IMC_PlayerInput'") };
		check(Asset.Succeeded());
		InputMappingContext = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_Move.IA_Move'") };
		check(Asset.Succeeded());
		Move = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_Look.IA_Look'") };
		check(Asset.Succeeded());
		Look = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_SpaceBar.IA_SpaceBar'") };
		check(Asset.Succeeded());
		Jump = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_Shift.IA_Shift'") };
		check(Asset.Succeeded());
		Shift = Asset.Object;
	}
}

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(InputMappingContext, 0);
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		{
			EnhancedInputComponent->BindAction(Move, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
			EnhancedInputComponent->BindAction(Look, ETriggerEvent::Triggered, this, &ThisClass::OnLookMouse);

		}
		{
			EnhancedInputComponent->BindAction(Shift, ETriggerEvent::Triggered, this, &ThisClass::OnShift);
			EnhancedInputComponent->BindAction(Shift, ETriggerEvent::Completed, this, &ThisClass::OffShift);
			EnhancedInputComponent->BindAction(Jump, ETriggerEvent::Triggered, this, &ThisClass::OnJump);
			EnhancedInputComponent->BindAction(Jump, ETriggerEvent::Completed, this, &ThisClass::OffJump);
		}
	}
}

void ACPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	APawn* ControlledPawn = GetPawn();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	
	ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	
}

void ACPlayerController::OnLookMouse(const FInputActionValue& InputActionValue)
{
	const FVector ActionValue = InputActionValue.Get<FVector>();
	AddYawInput(ActionValue.X);
	AddPitchInput(ActionValue.Y);
}

void ACPlayerController::OnShift(const FInputActionValue& InputActionValue)
{
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	if (!player) return;
	player->OnShift();
}

void ACPlayerController::OffShift(const FInputActionValue& InputActionValue)
{
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	if (!player) return;
	player->OffShift();
}

void ACPlayerController::OnJump(const FInputActionValue& InputActionValue)
{
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	if (!player) return;
	player->Jump();
}

void ACPlayerController::OffJump(const FInputActionValue& InputActionValue)
{
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	if (!player) return;
	player->StopJumping();
}
