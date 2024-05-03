#include "Components/StateComponent.h"
#include "GameFramework/Character.h"
#include "Components/EquipComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Actors/Weapon/Melee/MeleeWeapon.h"

UStateComponent::UStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UStateComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


bool UStateComponent::IsCanCombo()
{
	UEquipComponent* equip = OwnerCharacter->GetComponentByClass<UEquipComponent>();
	if(!equip) return false;

	AMeleeWeapon* weapon = Cast<AMeleeWeapon>(equip->GetCurrentItem());
	if (!weapon) return false;

	return weapon->IsCanCombo();
}

void UStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UStateComponent::SetEquipMode()
{
	ChangeType(EStateType::Equip);
}

void UStateComponent::SetActionMode()
{
	ChangeType(EStateType::Action);
}

void UStateComponent::SetHittedMode()
{
	ChangeType(EStateType::Hitted);
}

void UStateComponent::SetDeadMode()
{
	ChangeType(EStateType::Dead);
}

void UStateComponent::SetOnOrient()
{
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void UStateComponent::SetOffOrient()
{
	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void UStateComponent::ChangeType(EStateType InNewType)
{
	EStateType prevType = Type;
	Type = InNewType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(prevType, Type);
}