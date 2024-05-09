#include "Behavior/BTTask_Move.h"
#include "Characters/Controller/BossAIController.h"
#include "Characters/AI/AIBoss.h"
#include "Components/BehaviorComponent.h"
#include "Components/StateComponent.h"
#include "Components/ActionComponent.h"

#include "GameFrameWork/Character.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BTTask_Move)

UBTTask_Move::UBTTask_Move()
{
	NodeName = "Move";

	bNotifyTick = true;

	// accept only actors and vectors
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Move, BlackboardKey), AActor::StaticClass());
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Move, BlackboardKey));
}

EBTNodeResult::Type UBTTask_Move::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABossAIController* controller = Cast<ABossAIController>(OwnerComp.GetOwner());
	
	AAIBoss* aiPawn = Cast<AAIBoss>(controller->GetPawn());

	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	if (MyBlackboard)
	{
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
		{
			UObject* KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
			AActor* TargetActor = Cast<AActor>(KeyValue);
			if (TargetActor)
			{
				aiPawn->SetMoveDirection(TargetActor->GetActorLocation());
				return EBTNodeResult::Succeeded;
			}
		}

		else if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		{
			const FVector TargetLocation = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
			aiPawn->SetMoveDirection(TargetLocation);
			return EBTNodeResult::Succeeded;
		}

	}
	return EBTNodeResult::Failed;
}

void UBTTask_Move::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
