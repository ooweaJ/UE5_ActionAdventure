#include "Components/StatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UStatusComponent::UStatusComponent()
{
}

void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UStatusComponent::SetMove()
{
	bCanMove = true;
}

void UStatusComponent::SetStop()
{
	bCanMove = false;
}

void UStatusComponent::SetSpeed(EWalkSpeedTpye InType)
{
	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(GetOwner()->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	movement->MaxWalkSpeed = Speed[(int32)InType];
}

