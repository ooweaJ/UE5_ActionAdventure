#include "Behavior/BTTask_BossAction.h"
#include "Characters/Controller/BossAIController.h"
#include "Characters/AI/AIBoss.h"
#include "Components/BossBehaviorComponent.h"
#include "Components/StateComponent.h"

#include "GameFrameWork/Character.h"

UBTTask_BossAction::UBTTask_BossAction()
{
	NodeName = "BossAction";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_BossAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABossAIController* controller = Cast<ABossAIController>(OwnerComp.GetOwner());
	if (!controller) return EBTNodeResult::Failed;

	UBossBehaviorComponent* behavior = controller->GetComponentByClass<UBossBehaviorComponent>();
	if (!behavior) return EBTNodeResult::Failed;

	AAIBoss* aiPawn = Cast<AAIBoss>(controller->GetPawn());
	UStateComponent* state = aiPawn->GetComponentByClass<UStateComponent>();

	if (!state->IsIdleMode()) return EBTNodeResult::Failed;

	behavior->bCanAction = false;
	aiPawn->DiceAction();

	return EBTNodeResult::InProgress;
}

void UBTTask_BossAction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ABossAIController* controller = Cast<ABossAIController>(OwnerComp.GetOwner());
	if (!controller) return;

	UBossBehaviorComponent* behavior = controller->GetComponentByClass<UBossBehaviorComponent>();
	if (!behavior) return;

	AAIBoss* aiPawn = Cast<AAIBoss>(controller->GetPawn());
	UStateComponent* state = aiPawn->GetComponentByClass<UStateComponent>();

	if (state->IsIdleMode())
	{
		behavior->bCanAction = true;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}