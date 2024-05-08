#include "Behavior/BTService_Boss.h"
#include "Characters/Controller/BossAIController.h"
#include "Characters/AI/AIBoss.h"
#include "Components/BehaviorComponent.h"
#include "Components/StateComponent.h"

#include "GameFrameWork/Character.h"

UBTService_Boss::UBTService_Boss()
{
	NodeName = "Boss";
}

void UBTService_Boss::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ABossAIController* controller = Cast<ABossAIController>(OwnerComp.GetOwner());
	if (!controller) return;

	UBehaviorComponent* behavior = controller->GetComponentByClass<UBehaviorComponent>();
	if (!behavior) return;

	AAIBoss* aiPawn = Cast<AAIBoss>(controller->GetPawn());
	UStateComponent* state = aiPawn->GetComponentByClass<UStateComponent>();

	ACharacter* target = behavior->GetTarget();

	if (state->IsKnockBackMode())
	{
		behavior->SetKnockBackMode();
		return;
	}

	if (target == nullptr)
	{
		behavior->SetPatrolMode();
		return;
	}

	controller->K2_SetFocus(target);

	if (behavior->bDoOnce == false)
	{
		behavior->bDoOnce = true;
		behavior->SetEquipMode();
		return;
	}

	float distance = aiPawn->GetDistanceTo(target);

	if (distance < controller->GetAttackRange())
	{
		state->SetOffOrient();
		FVector TargetLocation = target->GetActorLocation();
		FVector AILocation = aiPawn->GetActorLocation();

		FVector DirectionToTarget = (TargetLocation - AILocation).GetSafeNormal();
		FVector AIForwardVector = aiPawn->GetActorForwardVector();

		float DotProduct = FVector::DotProduct(DirectionToTarget, AIForwardVector);

		if (DotProduct > 0.8f)
		{
			//state->SetOnOrient();
			behavior->SetActionMode();
			return;
		}
	}
	else
	{
		behavior->SetApproachMode();
		return;
	}
}
