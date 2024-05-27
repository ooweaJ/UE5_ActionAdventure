#include "Characters/CAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

#include "Components/MoveComponent.h"
#include "Components/ActionComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	MoveComp = Cast<UMoveComponent>(TryGetPawnOwner()->GetComponentByClass(UMoveComponent::StaticClass()));

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	if (!IsValid(character)) return;
	Action = Cast<UActionComponent>(character->GetComponentByClass(UActionComponent::StaticClass()));
	Action->OnActionTypeChanged.AddDynamic(this, &ThisClass::OnActionTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	if (!IsValid(character)) return;
	Speed = character->GetVelocity().Length();
	Direction = UKismetAnimationLibrary::CalculateDirection(character->GetVelocity(), character->GetControlRotation());
	IsFalling = character->GetCharacterMovement()->IsFalling();
	Pitch = character->GetBaseAimRotation().Pitch;
	if(!!Action)
	IsAiming = Action->IsAiming();

	if (!!MoveComp)
		Axis = MoveComp->GetLeanAxis();
}

void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}

