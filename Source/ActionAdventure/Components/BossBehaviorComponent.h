#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BossBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBossType : uint8
{
	Strafe, Avoid, Melee, 
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

	void SetWaitMode();
	void SetApproachMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();
	void SetKnockBackMode();
	void SetEquipMode();


private:
	void ChangeType(EBossType InType);
	EBossType GetType();

private:
	UPROPERTY(EditAnywhere) FName BehaviorKey = "Behavior";
	UPROPERTY(EditAnywhere) FName TargetKey = "Target";
	UPROPERTY(EditAnywhere) FName LocationKey = "Location";

private:
	class UBlackboardComponent* Blackboard;
};
