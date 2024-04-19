#include "Components/BehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFrameWork/Character.h"

UBehaviorComponent::UBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

ACharacter* UBehaviorComponent::GetTarget()
{
	ACharacter* character = Cast<ACharacter>(Blackboard->GetValueAsObject(TargetKey));
	if (!!character)
		return character;
	return nullptr;
}

FVector UBehaviorComponent::GetLocation()
{
	return Blackboard->GetValueAsVector(LocationKey);
}

void UBehaviorComponent::SetWaitMode() { ChangeType(EBehaviorType::Wait); }
void UBehaviorComponent::SetApproachMode() { ChangeType(EBehaviorType::Approach); }
void UBehaviorComponent::SetActionMode(){ ChangeType(EBehaviorType::Action); }
void UBehaviorComponent::SetPatrolMode(){ ChangeType(EBehaviorType::patrol); }
void UBehaviorComponent::SetHittedMode(){ ChangeType(EBehaviorType::Hitted); }

void UBehaviorComponent::ChangeType(EBehaviorType InType)
{
	EBehaviorType type = GetType();
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InType);

	/*if (OnBehaviorTypeChanged.IsBound())
		OnBehaviorTypeChanged.Broadcast(type, InType);*/
}

EBehaviorType UBehaviorComponent::GetType()
{
	return (EBehaviorType)Blackboard->GetValueAsEnum(BehaviorKey);
}
