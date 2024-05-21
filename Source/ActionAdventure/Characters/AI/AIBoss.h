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

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void SetMoveDirection(const FVector Direction);
	void SetMoveDirection(const AActor* Actor);
	void DiceAction();
	void ApproachAction();
	void Avoid();
	void AvoidTarget();
	void MoveAlongPath(TArray<FVector> PathPoints, int32 CurrentPointIndex);
	void StrafeAttack();
	void RangeAttack();

	float GetDistanceToTarget();
public:
	FORCEINLINE bool IsRange() { return bRangeAttack; }
	FORCEINLINE bool IsAvoid() { return bAvoid; }
	FORCEINLINE bool IsPage2() { return Page2; }

	FRotator GetTargetRotation();
	
	class ABossAIController* GetBossController();

	bool IsTargetInFront();
	void RotateToTarget();
	void TargetRotation();

	void FoucsTarget();
	void ClearFoucsTarget();
	void OnTarget();
	void OffTarget();
	
	void StopMontage(class UAnimMontage* InMontage);

	UFUNCTION()
	void ResumeMontage(class UAnimMontage* InMontage);

	UFUNCTION(BlueprintImplementableEvent)
	void Page2Start();
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

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* TargetingWidget;

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
	class UUI_UserStatus* BossHPBar;
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

	TSubclassOf<class ABossRange> RangeSpawn;
	class ACharacter* Attacker;

	bool Page2;
	float Damage;
};
