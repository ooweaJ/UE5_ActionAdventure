#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Strafe.generated.h"

UCLASS()
class ACTIONADVENTURE_API UBTTask_Strafe : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Strafe();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FVector Direction;
	float MotionTime;
	bool bRight;
};
