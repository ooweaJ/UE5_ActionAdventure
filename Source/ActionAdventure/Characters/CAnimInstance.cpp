#include "Characters/CAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/MoveComponent.h"
#include "Components/ActionComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	MoveComp = Cast<UMoveComponent>(TryGetPawnOwner()->GetComponentByClass(UMoveComponent::StaticClass()));

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	if (!IsValid(character)) return;
	UActionComponent* Action = Cast<UActionComponent>(character->GetComponentByClass(UActionComponent::StaticClass()));
	Action->OnActionTypeChanged.AddDynamic(this, &ThisClass::OnActionTypeChanged);
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

void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}

