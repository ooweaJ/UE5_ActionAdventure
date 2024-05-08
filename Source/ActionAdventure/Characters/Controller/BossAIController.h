#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossAIController.generated.h"

UCLASS()
class ACTIONADVENTURE_API ABossAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABossAIController();

public:
	void SetLoactionKey(FVector InLoaction);
	void SetTargetKey(class ACharacter* InCharacter);
	void MoveToLocation(const FVector Destination);

public:
	FORCEINLINE	void SetAttackRange(float Range) { AttackRange = Range; }
	FORCEINLINE float GetAttackRange() { return AttackRange; }
	FORCEINLINE class UBossBehaviorComponent* GetBehavior() { return Behavior; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	class UBossBehaviorComponent* Behavior;

	UPROPERTY(VisibleDefaultsOnly)
	class UAIPerceptionComponent* Perception;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
private:
	class AAIBoss* OwnerAI;
	class UAISenseConfig_Sight* Sight;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;

	float AttackRange = 100.f;
};
