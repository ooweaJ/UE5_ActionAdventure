#include "Components/StateComponent.h"

UStateComponent::UStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

