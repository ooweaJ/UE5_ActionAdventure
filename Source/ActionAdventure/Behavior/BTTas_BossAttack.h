#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTas_BossAttack.generated.h"

UCLASS()
class ACTIONADVENTURE_API UBTTas_BossAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTas_BossAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
