#include "Characters/CAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	if (!IsValid(character)) return;

	ACPlayer* Player = Cast<ACPlayer>(character);
	if (!IsValid(Player)) return;

	Player->OnMoveDirection.AddDynamic(this, &ThisClass::OnMoveDirectionChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	if (!IsValid(character)) return;

	Speed = character->GetVelocity().Length();
	Direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());
	IsFalling = character->GetCharacterMovement()->IsFalling();

	ACPlayer* Player = Cast<ACPlayer>(character);
	if (!IsValid(Player)) return;
	Axis = Player->LeanAxis;
}

void UCAnimInstance::OnMoveDirectionChanged(EMoveDirection InMoveDirection)
{
	MoveDirection = InMoveDirection;

}

