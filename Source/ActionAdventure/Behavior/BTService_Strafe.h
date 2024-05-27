#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Strafe.generated.h"

UCLASS()
class ACTIONADVENTURE_API UBTService_Strafe : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_Strafe();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
