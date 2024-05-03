#include "Behavior/BTService_AI.h"
#include "Characters/Controller/CAIController.h"
#include "Characters/AI/AICharacter.h"
#include "Components/BehaviorComponent.h"
#include "Components/StateComponent.h"

#include "GameFrameWork/Character.h"

UBTService_AI::UBTService_AI()
{
	NodeName = "AI";
}

void UBTService_AI::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	if (!controller) return;

	UBehaviorComponent* behavior = controller->GetComponentByClass<UBehaviorComponent>();
	if (!behavior) return;

	AAICharacter* aiPawn = Cast<AAICharacter>(controller->GetPawn());
	UStateComponent* state =aiPawn->GetComponentByClass<UStateComponent>();

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
