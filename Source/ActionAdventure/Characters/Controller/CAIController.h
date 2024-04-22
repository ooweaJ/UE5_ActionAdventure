#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

UCLASS()
class ACTIONADVENTURE_API ACAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACAIController();
	
public:
	void SetLoactionKey(FVector InLoaction);
	void SetTargetKey(class ACharacter* InCharacter);
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	class UBehaviorComponent* Behavior;

	UPROPERTY(VisibleDefaultsOnly)
	class UAIPerceptionComponent* Perception;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
private:
	class AAICharacter* OwnerAI;
	class UAISenseConfig_Sight* Sight;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
