#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIBoss.generated.h"

UCLASS()
class ACTIONADVENTURE_API AAIBoss : public ACharacter
{
	GENERATED_BODY()

public:
	AAIBoss();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetMoveDirection(const FVector Direction);
	void SetMoveDirection(const AActor* Actor);
	void DiceAction();
	void ApproachAction();
	void Avoid();
	void AvoidTarget();
	void MoveAlongPath(TArray<FVector> PathPoints, int32 CurrentPointIndex);
	void StrafeAttack();

	float GetDistanceToTarget();
public:
	FORCEINLINE bool IsRange() { return bRangeAttack; }
	FORCEINLINE bool IsAvoid() { return bAvoid; }
	
	class ABossAIController* GetBossController();

	void RotateToTarget();
	bool IsTargetInFront();
	void TargetRotation();

	void FoucsTarget();
	void ClearFoucsTarget();

	void StopMontage(class UAnimMontage* InMontage);
	UFUNCTION()
	void ResumeMontage(class UAnimMontage* InMontage);
public:
	UPROPERTY(VisibleDefaultsOnly)
	class UStatusComponent* StatusComponent;

	UPROPERTY(VisibleDefaultsOnly)
	class UStateComponent* StateComponent;

	UPROPERTY(VisibleDefaultsOnly)
	class UMoveComponent* MoveComponent;

	UPROPERTY(VisibleDefaultsOnly)
	class UActionComponent* ActionComponent;

	UPROPERTY(VisibleDefaultsOnly)
	class UEquipComponent* EquipComponent;

	UPROPERTY(VisibleDefaultsOnly)

	class UPaperSpriteComponent* PaperComponent;

	UPROPERTY(VisibleDefaultsOnly)
	class UMontagesComponent* MontagesComponent;
	class UAnimMontage* CastMontage;

	class UBossBehaviorComponent* Behavior;
public:
	UPROPERTY(BlueprintReadOnly)
	FVector MovingDirection;

	bool ApproachEnd = false;
	bool bTargetRotation = false;

	int32 StrafeAttackConunt = 3;
private:
	class ABossAIController* BossController;
	class ABossWeapon* Weapon;

private:
	bool bRangeAttack = true;
	float MaxRangeCoolTime = 30.f;
	float RangeCoolTime = 0.f;

	bool bAvoid = true;
	float MaxAvoidCollTime = 8.f;
	float AvoidCollTime = 0.f;

private:
	FVector TargetLocation;

	FTimerHandle TimerHandle;


};
