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

    FVector TargetLocation = Target->GetActorLocation();
    FVector AILocation = aiPawn->GetActorLocation();

    // 타겟을 중심으로 한 방향 벡터 계산
    FVector DirectionToTarget = (AILocation - TargetLocation).GetSafeNormal();

    // 각도 계산
    float YawAngle = FMath::DegreesToRadians(GetWorld()->GetTimeSeconds() * 100.f);

    // 원형으로 이동하는 벡터 계산
    FVector CircleMovement = FVector(FMath::Cos(YawAngle), FMath::Sin(YawAngle), 0.0f) * distance;

    // 타겟 중심으로 이동하는 벡터에 회전 벡터를 더하여 이동 방향 설정
    FVector MoveDirection = (DirectionToTarget * distance) + CircleMovement;

    // 이동 방향 설정
    MoveDirection.Normalize();

    GEngine->AddOnScreenDebugMessage(1, 1, FColor::Black, "Hi");
    controller->SetLoactionKey(MoveDirection);
}
