#include "Behavior/BTTask_Combat.h"
#include "Characters/Controller/CAIController.h"
#include "Characters/AI/AICharacter.h"
#include "Components/BehaviorComponent.h"
#include "Components/StateComponent.h"
#include "Components/EquipComponent.h"

#include "GameFrameWork/Character.h"

UBTTask_Combat::UBTTask_Combat()
{
	NodeName = "Combat";

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Combat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());

	AAICharacter* aiPawn = Cast<AAICharacter>(controller->GetPawn());
	UEquipComponent* Equip = aiPawn->GetComponentByClass<UEquipComponent>();
	
	if (Equip)
	{
		Equip->AICombat();

		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UBTTask_Combat::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());
	AAICharacter* aiPawn = Cast<AAICharacter>(controller->GetPawn());
	UBehaviorComponent* behavior = controller->GetComponentByClass<UBehaviorComponent>();
	UStateComponent* State = aiPawn->GetComponentByClass<UStateComponent>();

	if (State->IsIdleMode())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
