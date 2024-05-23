#include "Behavior/BTTask_LastAttack.h"
#include "Characters/Controller/BossAIController.h"
#include "Characters/AI/AIBoss.h"
#include "Components/BossBehaviorComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"

#include "GameFrameWork/Character.h"

UBTTask_LastAttack::UBTTask_LastAttack()
{
	NodeName = "LastAttack";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_LastAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABossAIController* controller = Cast<ABossAIController>(OwnerComp.GetOwner());
	if (!controller) return EBTNodeResult::Failed;

	UBossBehaviorComponent* behavior = controller->GetComponentByClass<UBossBehaviorComponent>();
	if (!behavior) return EBTNodeResult::Failed;

	AAIBoss* aiPawn = Cast<AAIBoss>(controller->GetPawn());
	UStateComponent* state = aiPawn->GetComponentByClass<UStateComponent>();
	UStatusComponent* status = aiPawn->GetComponentByClass<UStatusComponent>();


	status->SetStop();
	state->SetActionMode();
	behavior->bCanAction = false;

	return EBTNodeResult::InProgress;
}

void UBTTask_LastAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ABossAIController* controller = Cast<ABossAIController>(OwnerComp.GetOwner());
	if (!controller) return;

	UBossBehaviorComponent* behavior = controller->GetComponentByClass<UBossBehaviorComponent>();
	if (!behavior) return;

	AAIBoss* aiPawn = Cast<AAIBoss>(controller->GetPawn());
	UStateComponent* state = aiPawn->GetComponentByClass<UStateComponent>();

	//if (state->IsIdleMode())
	//{
	//	behavior->bCanAction = true;
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//}
}
