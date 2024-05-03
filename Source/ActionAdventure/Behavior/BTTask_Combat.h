#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Combat.generated.h"


UCLASS()
class ACTIONADVENTURE_API UBTTask_Combat : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Combat();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};