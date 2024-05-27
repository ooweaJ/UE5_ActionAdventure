#include "Behavior/Task_Dead.h"
#include "Characters/Controller/BossAIController.h"
#include "Characters/AI/AIBoss.h"
#include "Components/BossBehaviorComponent.h"
#include "Components/StateComponent.h"

#include "GameFrameWork/Character.h"

UTask_Dead::UTask_Dead()
{
	NodeName = "BossDead";
	bNotifyTick = true;
}

EBTNodeResult::Type UTask_Dead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABossAIController* controller = Cast<ABossAIController>(OwnerComp.GetOwner());
	if (!controller) return EBTNodeResult::Failed;

	UBossBehaviorComponent* behavior = controller->GetComponentByClass<UBossBehaviorComponent>();
	if (!behavior) return EBTNodeResult::Failed;

	AAIBoss* aiPawn = Cast<AAIBoss>(controller->GetPawn());
	UStateComponent* state = aiPawn->GetComponentByClass<UStateComponent>();

	behavior->bCanAction = false;
	aiPawn->Dead();

	return EBTNodeResult::InProgress;
}

void UTask_Dead::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
