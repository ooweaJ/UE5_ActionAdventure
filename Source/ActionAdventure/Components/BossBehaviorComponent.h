#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BossBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBossType : uint8
{
	Action, Approach, ApproachAction, Strafe, StrafeAction, Hitted, Avoid, Page2, LastAttack
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONADVENTURE_API UBossBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBossBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE void SetBlackBoard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }
	class ACharacter* GetTarget();
	FVector GetLocation();

	bool IsStrafe();
	bool IsStrafeAction();

	void SetAction();
	void SetApproach();
	void SetApproachAction();
	void SetStrafe();
	void SetStrafeAction();
	void SetHitted();
	void SetAvoid();
	void SetIdle(bool InIdle);
	void SetPage2();
	void SetLastAttack();

private:
	void ChangeType(EBossType InType);
	EBossType GetType();
public:
	bool bCanAction = true;
private:
	UPROPERTY(EditAnywhere) FName BehaviorKey = "Behavior";
	UPROPERTY(EditAnywhere) FName TargetKey = "Target";
	UPROPERTY(EditAnywhere) FName LocationKey = "Location";
	UPROPERTY(EditAnywhere) FName IdleKey = "IsIdle";

private:
	class UBlackboardComponent* Blackboard;
};
