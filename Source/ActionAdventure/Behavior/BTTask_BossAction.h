#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BossAction.generated.h"


UCLASS()
class ACTIONADVENTURE_API UBTTask_BossAction : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_BossAction();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
