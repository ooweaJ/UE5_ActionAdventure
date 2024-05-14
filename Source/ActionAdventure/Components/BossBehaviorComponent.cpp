#include "Components/BossBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFrameWork/Character.h"

UBossBehaviorComponent::UBossBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UBossBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
	SetIdle(true);
}

void UBossBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

ACharacter* UBossBehaviorComponent::GetTarget()
{
	ACharacter* character = Cast<ACharacter>(Blackboard->GetValueAsObject(TargetKey));
	if (!!character)
		return character;
	return nullptr;
}

FVector UBossBehaviorComponent::GetLocation()
{
	return FVector();
}

void UBossBehaviorComponent::SetAction() { ChangeType(EBossType::Action); }
void UBossBehaviorComponent::SetApproach() { ChangeType(EBossType::Approach); }
void UBossBehaviorComponent::SetApproachAction() { ChangeType(EBossType::ApproachAction); }
void UBossBehaviorComponent::SetStrafe() { ChangeType(EBossType::Strafe); }
void UBossBehaviorComponent::SetStrafeAction() { ChangeType(EBossType::StrafeAction); }
void UBossBehaviorComponent::SetHitted() { ChangeType(EBossType::Hitted); }
void UBossBehaviorComponent::SetAvoid() { ChangeType(EBossType::Avoid); }
void UBossBehaviorComponent::SetIdle(bool InIdle) { Blackboard->SetValueAsBool(IdleKey, InIdle); }

void UBossBehaviorComponent::ChangeType(EBossType InType)
{
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InType);
}
