#include "Behavior/BTTask_Patrol.h"
#include "Components/BehaviorComponent.h"
#include "Components/StateComponent.h"
#include "Characters/AI/AICharacter.h"
#include "Characters/Controller/CAIController.h"

#include "Navigation/PathFollowingComponent.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = "Patrol";

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	AAICharacter* aiPawn = Cast<AAICharacter>(controller->GetPawn());
	UBehaviorComponent* behavior = controller->GetComponentByClass<UBehaviorComponent>();
	UStateComponent* State = aiPawn->GetComponentByClass<UStateComponent>();

	if (State->IsIdleMode() == false) return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	AAICharacter* aiPawn = Cast<AAICharacter>(controller->GetPawn());
	UBehaviorComponent* behavior = controller->GetComponentByClass<UBehaviorComponent>();
	UStateComponent* State = aiPawn->GetComponentByClass<UStateComponent>();
	if (State->IsIdleMode() == false) return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	FVector location;
	location = behavior->GetLocation();
	EPathFollowingRequestResult::Type type = controller->MoveToLocation(location);

	if (type == EPathFollowingRequestResult::Type::Failed)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (type == EPathFollowingRequestResult::Type::AlreadyAtGoal)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
