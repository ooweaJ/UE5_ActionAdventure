#include "Characters/Controller/CPlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Characters/Players/CPlayer.h"
#include "Data/Input/InPutDataConfig.h"
#include "Components/StatusComponent.h"
#include "SubSystem/InventorySubsystem.h"

ACPlayerController::ACPlayerController()
{
}

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	const UInPutDataConfig* InPutDataConfig = GetDefault<UInPutDataConfig>();
	Subsystem->AddMappingContext(InPutDataConfig->InputMappingContext, 0);
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		const UInPutDataConfig* InPutDataConfig = GetDefault<UInPutDataConfig>();
		{
			EnhancedInputComponent->BindAction(InPutDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
			EnhancedInputComponent->BindAction(InPutDataConfig->Look, ETriggerEvent::Triggered, this, &ThisClass::OnLookMouse);

		}
		{
			EnhancedInputComponent->BindAction(InPutDataConfig->Shift, ETriggerEvent::Triggered, this, &ThisClass::OnShift);
			EnhancedInputComponent->BindAction(InPutDataConfig->Shift, ETriggerEvent::Completed, this, &ThisClass::OffShift);
			EnhancedInputComponent->BindAction(InPutDataConfig->Jump, ETriggerEvent::Triggered, this, &ThisClass::OnJump);
			EnhancedInputComponent->BindAction(InPutDataConfig->Jump, ETriggerEvent::Completed, this, &ThisClass::OffJump);
			EnhancedInputComponent->BindAction(InPutDataConfig->MouseL, ETriggerEvent::Triggered, this, &ThisClass::OnMouseL);
			EnhancedInputComponent->BindAction(InPutDataConfig->MouseR, ETriggerEvent::Triggered, this, &ThisClass::OnMouseR);
			EnhancedInputComponent->BindAction(InPutDataConfig->MouseR, ETriggerEvent::Completed, this, &ThisClass::OffMouseR);
			EnhancedInputComponent->BindAction(InPutDataConfig->Num1, ETriggerEvent::Started, this, &ThisClass::OnNum1);
			EnhancedInputComponent->BindAction(InPutDataConfig->Num2, ETriggerEvent::Started, this, &ThisClass::OnNum2);
			EnhancedInputComponent->BindAction(InPutDataConfig->Num3, ETriggerEvent::Started, this, &ThisClass::OnNum3);
			EnhancedInputComponent->BindAction(InPutDataConfig->T, ETriggerEvent::Started, this, &ThisClass::OnT);
		}
	}
}

void ACPlayerController::OnPossess(APawn* aPawn)
{
	UInventorySubsystem* InventorySubsystem = ULocalPlayer::GetSubsystem<UInventorySubsystem>(GetLocalPlayer());
	InventorySubsystem->MakeInventory();

	Super::OnPossess(aPawn);

	LoadClass<UClass>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/UI_PlayerMain.UI_PlayerMain_C'"),
		nullptr, LOAD_None, nullptr);
	UClass* WidgetClass = FindObject<UClass>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/UI_PlayerMain.UI_PlayerMain_C'"));
	MainWidget = CreateWidget<UPlayerMainWidget>(GetWorld(), WidgetClass);
	MainWidget->AddToViewport();
}

void ACPlayerController::OnUnPossess()
{
	
}

void ACPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	APawn* ControlledPawn = GetPawn();

	UStatusComponent* Status = Cast<UStatusComponent>(ControlledPawn->GetComponentByClass<UStatusComponent>());
	if (!Status) return;
	if (!Status->IsCanMove()) return;

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
	if (player->IsComBat())
		player->OnRoll();
	else
		player->Jump();
}

void ACPlayerController::OffJump(const FInputActionValue& InputActionValue)
{
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	if (!player) return;
	player->StopJumping();
}

void ACPlayerController::OnMouseL(const FInputActionValue& InputActionValue)
{
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	if (!player) return;
	player->OnMouseL();
}

void ACPlayerController::OnMouseR(const FInputActionValue& InputActionValue)
{
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	if (!player) return;
	player->OnMouseR();
}

void ACPlayerController::OffMouseR(const FInputActionValue& InputActionValue)
{
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	if (!player) return;
	player->OffMouseR();
}

void ACPlayerController::OnNum1(const FInputActionValue& InputActionValue)
{
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	if (!player) return;
	player->OnNum1();
}

void ACPlayerController::OnNum2(const FInputActionValue& InputActionValue)
{
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	if (!player) return;
	player->OnNum2();
}

void ACPlayerController::OnNum3(const FInputActionValue& InputActionValue)
{
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	if (!player) return;
	player->OnNum3();
}

void ACPlayerController::OnG(const FInputActionValue& InputActionValue)
{
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	if (!player) return;
	player->Parkour();
}

void ACPlayerController::OnT(const FInputActionValue& InputActionValue)
{
	ACPlayer* player = Cast<ACPlayer>(GetPawn());
	if (!player) return;
	player->OnT();
}
