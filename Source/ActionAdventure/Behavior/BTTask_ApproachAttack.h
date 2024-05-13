// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ApproachAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONADVENTURE_API UBTTask_ApproachAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ApproachAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
