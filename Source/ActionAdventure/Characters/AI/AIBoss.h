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

public:
	FORCEINLINE bool IsRange() { return bRangeAttack; }

private:
	float GetDistanceToTarget();

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

public:
	UPROPERTY(BlueprintReadOnly)
	FVector MovingDirection;

private:
	class ABossAIController* BossController;

private:
	bool bRangeAttack = true;
	float MaxRangeCoolTime = 30.f;
	float RangeCoolTime = 0.f;
};
