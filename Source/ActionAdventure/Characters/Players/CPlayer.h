#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UENUM(BlueprintType)
enum class EMoveDirection : uint8
{
	None, Right, Left
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMoveDirection, EMoveDirection, InMoveDirection);

UCLASS()
class ACTIONADVENTURE_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// 입력 받아서 회전시키는 함수
	void RotateTowardsMovementDirection(float DeltaTime);

public:
	void OnShift();
	void OffShift();

	// 현재 회전 방향
	FRotator TargetRotation;

	float LeanAxis;
	// 회전 보간 속도
	UPROPERTY(EditAnywhere)
	float RotationInterpSpeed;

	UPROPERTY(EditAnywhere)
	float MinWalkSpeed;

	UPROPERTY(EditAnywhere)
	float MaxWalkSpeed;

	UPROPERTY(EditAnywhere)
	EMoveDirection MoveDirection ;

	UPROPERTY(BlueprintAssignable)
	FMoveDirection OnMoveDirection;

	float AimYawRate;
	float PreviousAimYaw;
	FRotator LastVelocity;
};
