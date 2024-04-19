#include "Components/StatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UStatusComponent::UStatusComponent()
{
	Health = MaxHealth;
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

void UStatusComponent::IncreaseHealth(float InAmount)
{
	Health += InAmount;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
}

void UStatusComponent::DecreaseHealth(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
}

