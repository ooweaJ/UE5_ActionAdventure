#include "Characters/CAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/MoveComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	MoveComp = Cast<UMoveComponent>(TryGetPawnOwner()->GetComponentByClass(UMoveComponent::StaticClass()));
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	if (!IsValid(character)) return;

	Speed = character->GetVelocity().Length();
	Direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());
	IsFalling = character->GetCharacterMovement()->IsFalling();

	if (!!MoveComp)
		Axis = MoveComp->GetLeanAxis();
}

