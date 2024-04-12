#include "Components/MoveComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"

#include "Characters/CAnimInstance.h"
UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	RotationInterpSpeed = 8.f;
}


void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerPawn = Cast<APawn>(GetOwner());
	
}

void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RotateTowardsMovementDirection(DeltaTime);
}

void UMoveComponent::RotateTowardsMovementDirection(float DeltaTime)
{
	if (!OwnerPawn) return;
	FVector Velocity = OwnerPawn->GetVelocity();
	FVector Forward = UKismetMathLibrary::LessLess_VectorRotator(Velocity, OwnerPawn->GetActorRotation());
	Forward = Forward / 350.0f;
	LeanAxis = FMath::FInterpTo(LeanAxis, Forward.Y, DeltaTime, 4.f);

	FVector MovementDirection = Velocity;
	if (!MovementDirection.IsNearlyZero())
	{
		FRotator DesiredRotation = MovementDirection.Rotation();
		TargetRotation = FMath::RInterpTo(TargetRotation, DesiredRotation, DeltaTime, RotationInterpSpeed);
		OwnerPawn->SetActorRotation(TargetRotation);
	}

}

