#include "Behavior/BTService_Strafe.h"
#include "Characters/Controller/BossAIController.h"
#include "Characters/AI/AIBoss.h"
#include "Components/BossBehaviorComponent.h"
#include "Components/StateComponent.h"

#include "GameFrameWork/Character.h"
#include "Engine.h"

UBTService_Strafe::UBTService_Strafe()
{
	NodeName = "Strafe";
}

void UBTService_Strafe::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	controller->SetFocus(Target);

	FVector AILocation = aiPawn->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	// AI가 타겟을 향해 향하는 방향 벡터 계산
	FVector DirectionToTarget = (TargetLocation - AILocation).GetSafeNormal();

	// 랜덤한 좌우 이동 벡터 생성
	float RandomOffset = FMath::RandRange(-1.0f, 1.0f); // -1에서 1 사이의 랜덤 값
	FVector RandomDirection = FVector(DirectionToTarget.Y + RandomOffset, -DirectionToTarget.X, 0.0f);

	// 이동 방향 설정
	FVector MoveDirection = RandomDirection.GetSafeNormal();

    controller->SetLoactionKey(MoveDirection);
}
