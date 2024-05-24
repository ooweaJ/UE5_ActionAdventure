#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_Dead.generated.h"

UCLASS()
class ACTIONADVENTURE_API UTask_Dead : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_Dead();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
