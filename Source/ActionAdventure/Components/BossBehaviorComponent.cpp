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

