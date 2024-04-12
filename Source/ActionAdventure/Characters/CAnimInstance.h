#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/Players/CPlayer.h"
#include "CAnimInstance.generated.h"

UCLASS()
class ACTIONADVENTURE_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Axis;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool IsFalling;

private:
	class UMoveComponent* MoveComp;
};
