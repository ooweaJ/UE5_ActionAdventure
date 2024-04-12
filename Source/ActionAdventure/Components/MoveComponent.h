#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONADVENTURE_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMoveComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE float GetLeanAxis() { return LeanAxis; }

private:
	void RotateTowardsMovementDirection(float DeltaTime);

private:
	UPROPERTY(EditAnywhere)
	float RotationInterpSpeed;

private:
	class APawn* OwnerPawn;
	FRotator TargetRotation;

	float LeanAxis;
};
