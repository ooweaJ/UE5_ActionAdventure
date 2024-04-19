#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BehaviorComponent.generated.h"


UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, patrol, Approach, Action, Hitted
};

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBehaviorTypeChanged, EBehaviorType, InPrevType, EBehaviorType, ChangeType);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONADVENTURE_API UBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBehaviorComponent();

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


private:
	void ChangeType(EBehaviorType InType);
	EBehaviorType GetType();

public:
	//UPROPERTY(BlueprintAssignable)
	//FBehaviorTypeChanged OnBehaviorTypeChanged;
private:
	UPROPERTY(EditAnywhere) FName BehaviorKey = "Behavior";
	UPROPERTY(EditAnywhere) FName TargetKey = "Target";
	UPROPERTY(EditAnywhere) FName LocationKey = "Location";

private:
	class UBlackboardComponent* Blackboard;
};