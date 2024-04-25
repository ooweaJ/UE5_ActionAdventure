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
	void OnMouseL(const FInputActionValue& InputActionValue);
	void OnMouseR(const FInputActionValue& InputActionValue);
	void OffMouseR(const FInputActionValue& InputActionValue);
	void OnNum1(const FInputActionValue& InputActionValue);
	void OnNum2(const FInputActionValue& InputActionValue);
	void OnNum3(const FInputActionValue& InputActionValue);
	void OnG(const FInputActionValue& InputActionValue);

public:

};
