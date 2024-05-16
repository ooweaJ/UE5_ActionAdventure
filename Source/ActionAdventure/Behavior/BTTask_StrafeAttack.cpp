#include "Behavior/BTTask_StrafeAttack.h"
#include "Characters/Controller/BossAIController.h"
#include "Characters/AI/AIBoss.h"
#include "Components/BossBehaviorComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"
#include "Components/ActionComponent.h"

#include "GameFrameWork/Character.h"
UBTTask_StrafeAttack::UBTTask_StrafeAttack()
{
	NodeName = "StrafeAttack";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_StrafeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABossAIController* controller = Cast<ABossAIController>(OwnerComp.GetOwner());
	if (!controller) return EBTNodeResult::Failed;

	UBossBehaviorComponent* behavior = controller->GetComponentByClass<UBossBehaviorComponent>();
	if (!behavior) return EBTNodeResult::Failed;

	AAIBoss* aiPawn = Cast<AAIBoss>(controller->GetPawn());
	UStateComponent* state = aiPawn->GetComponentByClass<UStateComponent>();

	if (!state->IsIdleMode()) return EBTNodeResult::Failed;
	if (!behavior->IsStrafeAction()) return EBTNodeResult::Failed;

	aiPawn->StrafeAttack();

	return EBTNodeResult::InProgress;
}

void UBTTask_StrafeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
