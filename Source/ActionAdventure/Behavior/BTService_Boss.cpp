#include "Behavior/BTService_Boss.h"
#include "Characters/Controller/BossAIController.h"
#include "Characters/AI/AIBoss.h"
#include "Components/BossBehaviorComponent.h"
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

	UBossBehaviorComponent* behavior = controller->GetComponentByClass<UBossBehaviorComponent>();
	if (!behavior) return;

	AAIBoss* aiPawn = Cast<AAIBoss>(controller->GetPawn());
	UStateComponent* state = aiPawn->GetComponentByClass<UStateComponent>();

	ACharacter* Target = behavior->GetTarget();

	float distance = aiPawn->GetDistanceTo(Target);

	if (!behavior->bCanAction) return;

	if (distance > 600.f)
	{
		if (aiPawn->IsRange())
		{
			behavior->SetAction();
			return;
		}
		else
		{
			behavior->SetApproach();
			return;
		}
	}
	
	FVector AILocation = aiPawn->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();
	FVector DirectionToTarget = (TargetLocation - AILocation).GetSafeNormal();
	FVector AIForwardVector = aiPawn->GetActorForwardVector();

	float DotProduct = FVector::DotProduct(DirectionToTarget, AIForwardVector);
	if (DotProduct > 0.5)
	{
		if (distance > 200.f)
		{
			// 300 이상이기 때문에 Strafe와 ApproachAction이 사용 가능
			float RandomValue = FMath::FRand();

			if (RandomValue <= 0.2f)
			{
				if (0.5f < FMath::FRand())
				{
					behavior->SetStrafe();
					return;
				}
				behavior->SetStrafeAction();
				return;
			}
			else if (RandomValue > 0.2f && RandomValue <= 0.6f)
			{
				behavior->SetApproachAction();
				return;
			}
			else
			{
				behavior->SetAction();
				return;
			}
		}
		else
		{
			behavior->SetAction();
			return;
		}
	}
	else
	{
		behavior->SetAvoid();
		return;
	}

	
	
}
