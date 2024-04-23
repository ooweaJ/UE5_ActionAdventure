#include "Behavior/Task_Speed.h"
#include "Characters/Controller/CAIController.h"
#include "Characters/AI/AICharacter.h"
#include "Components/BehaviorComponent.h"

UTask_Speed::UTask_Speed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UTask_Speed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());

	AAICharacter* aiPawn = Cast<AAICharacter>(controller->GetPawn());
	UBehaviorComponent* behavior = controller->GetComponentByClass<UBehaviorComponent>();
	UStatusComponent* Status = aiPawn->GetComponentByClass<UStatusComponent>();
	Status->SetSpeed(Type);

	return EBTNodeResult::Succeeded;
}
