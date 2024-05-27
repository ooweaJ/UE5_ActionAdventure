#include "Behavior/BTTask_Strafe.h"
#include "Characters/Controller/BossAIController.h"
#include "Characters/AI/AIBoss.h"
#include "Components/BossBehaviorComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"
#include "Components/ActionComponent.h"

#include "GameFrameWork/Character.h"

UBTTask_Strafe::UBTTask_Strafe()
{
	NodeName = "Strafe";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Strafe::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	UActionComponent* action = aiPawn->GetComponentByClass<UActionComponent>();

	ACharacter* Target = behavior->GetTarget();
	action->OnAim();
	behavior->bCanAction = false;
	status->SetSpeed(EWalkSpeedTpye::Sneak);
	controller->SetFocus(Target);
	state->SetOffOrient();

	float RandomValue = FMath::FRand();

	MotionTime = 0.0f;

	if (RandomValue < 0.5f)
	{
		bRight = true;
	}
	else
	{
		bRight = false;
	}

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_Strafe::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABossAIController* controller = Cast<ABossAIController>(OwnerComp.GetOwner());
	if (!controller) return EBTNodeResult::Failed;

	UBossBehaviorComponent* behavior = controller->GetComponentByClass<UBossBehaviorComponent>();
	if (!behavior) return EBTNodeResult::Failed;

	AAIBoss* aiPawn = Cast<AAIBoss>(controller->GetPawn());

	UStateComponent* state = aiPawn->GetComponentByClass<UStateComponent>();

	UStatusComponent* status = aiPawn->GetComponentByClass<UStatusComponent>();
	UActionComponent* action = aiPawn->GetComponentByClass<UActionComponent>();

	ACharacter* Target = behavior->GetTarget();
	action->OffAim();
	status->SetSpeed(EWalkSpeedTpye::Walk);
	state->SetOnOrient();
	controller->ClearFocus(EAIFocusPriority::Gameplay);

	return EBTNodeResult::Succeeded;
}

void UBTTask_Strafe::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ABossAIController* controller = Cast<ABossAIController>(OwnerComp.GetOwner());
	if (!controller) return;

	UBossBehaviorComponent* behavior = controller->GetComponentByClass<UBossBehaviorComponent>();
	if (!behavior) return;

	AAIBoss* aiPawn = Cast<AAIBoss>(controller->GetPawn());
	UStateComponent* state = aiPawn->GetComponentByClass<UStateComponent>();
	UStatusComponent* status = aiPawn->GetComponentByClass<UStatusComponent>();
	UActionComponent* action = aiPawn->GetComponentByClass<UActionComponent>();

	MotionTime += DeltaSeconds;

	if(bRight)
		Direction = aiPawn->GetActorRightVector();
	else
		Direction = -aiPawn->GetActorRightVector();

	aiPawn->SetMoveDirection(Direction);

	if (MotionTime >= 3.f)
	{
		action->OffAim();
		status->SetSpeed(EWalkSpeedTpye::Walk);
		state->SetOnOrient();
		controller->ClearFocus(EAIFocusPriority::Gameplay);
		behavior->bCanAction = true;
		aiPawn->StrafeAttackConunt = 3;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
