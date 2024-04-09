#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class ACTIONADVENTURE_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnLookMouse(const FInputActionValue& InputActionValue);

	void OnShift(const FInputActionValue& InputActionValue);
	void OffShift(const FInputActionValue& InputActionValue);
	void OnJump(const FInputActionValue& InputActionValue);
	void OffJump(const FInputActionValue& InputActionValue);

public:
	UInputMappingContext* InputMappingContext = nullptr;

	UInputAction* Move = nullptr;
	UInputAction* Look = nullptr;
	UInputAction* Jump = nullptr;
	UInputAction* Shift = nullptr;
};