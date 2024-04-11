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
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Axis = 1.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EMoveDirection MoveDirection;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
	void OnMoveDirectionChanged(EMoveDirection InMoveDirection);
};
