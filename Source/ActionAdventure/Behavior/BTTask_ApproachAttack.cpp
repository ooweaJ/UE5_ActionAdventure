#include "Behavior/BTTask_ApproachAttack.h"
#include "Characters/Controller/BossAIController.h"
#include "Characters/AI/AIBoss.h"
#include "Components/BossBehaviorComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"

#include "GameFrameWork/Character.h"

UBTTask_ApproachAttack::UBTTask_ApproachAttack()
{
	NodeName = "ApproachAttack";

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_ApproachAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABossAIController* controller = Cast<ABossAIController>(OwnerComp.GetOwner());
	if (!controller) return EBTNodeResult::Failed;

	UBossBehaviorComponent* behavior = controller->GetComponentByClass<UBossBehaviorComponent>();
	if (!behavior) return EBTNodeResult::Failed;

	AAIBoss* aiPawn = Cast<AAIBoss>(controller->GetPawn());

	UStateComponent* state = aiPawn->GetComponentByClass<UStateComponent>();
	if (!state->IsIdleMode()) return EBTNodeResult::Failed;


	UStatusComponent* status = aiPawn->GetComponentByClass<UStatusComponent>();

	behavior->bCanAction = false;


	state->SetApproachMode();
	status->SetSpeed(EWalkSpeedTpye::Run);

	return EBTNodeResult::InProgress;
}

void UBTTask_ApproachAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ABossAIController* controller = Cast<ABossAIController>(OwnerComp.GetOwner());
	if (!controller) return;

	UBossBehaviorComponent* behavior = controller->GetComponentByClass<UBossBehaviorComponent>();
	if (!behavior) return;

	AAIBoss* aiPawn = Cast<AAIBoss>(controller->GetPawn());
	UStateComponent* state = aiPawn->GetComponentByClass<UStateComponent>();
	UStatusComponent* status = aiPawn->GetComponentByClass<UStatusComponent>();

	float Distance = aiPawn->GetDistanceToTarget();
	ACharacter* target = behavior->GetTarget();
	aiPawn->SetMoveDirection(target);
	if (Distance < 200.f)
	{
		aiPawn->ApproachAction();
	}

	if (state->IsIdleMode())
	{
		behavior->bCanAction = true;
		status->SetSpeed(EWalkSpeedTpye::Walk);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
