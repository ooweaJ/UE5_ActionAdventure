#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/Players/CPlayer.h"
#include "Components/ActionComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class ACTIONADVENTURE_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
	void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Axis;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Pitch;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool IsAiming;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EActionType ActionType;
private:
	class UMoveComponent* MoveComp;
	class UActionComponent* Action;
};
