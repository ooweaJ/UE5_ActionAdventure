#include "Behavior/Task_Action.h"
#include "Characters/Controller/CAIController.h"
#include "Characters/AI/AICharacter.h"
#include "Components/BehaviorComponent.h"
#include "Components/StateComponent.h"
#include "Components/ActionComponent.h"

#include "GameFrameWork/Character.h"

UTask_Action::UTask_Action()
{
	NodeName = "Action";

	bNotifyTick = true;
}

EBTNodeResult::Type UTask_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());

	AAICharacter* aiPawn = Cast<AAICharacter>(controller->GetPawn());
	UActionComponent* action = aiPawn->GetComponentByClass<UActionComponent>();
	controller->StopMovement();
	action->MouseL();

	return EBTNodeResult::InProgress;
}

void UTask_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());

	AAICharacter* aiPawn = Cast<AAICharacter>(controller->GetPawn());
	UBehaviorComponent* behavior = controller->GetComponentByClass<UBehaviorComponent>();
	UStateComponent* State = aiPawn->GetComponentByClass<UStateComponent>();

	if (State->IsActionMode())
	{
		if(State->IsCanCombo())
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	if (State->IsIdleMode())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
