#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CPlayerController.generated.h"

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

public:
	class UInputMappingContext* InputMappingContext = nullptr;

	class UInputAction* Move = nullptr;
	class UInputAction* Look = nullptr;
};
