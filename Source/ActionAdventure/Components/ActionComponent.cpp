#include "Components/ActionComponent.h"
#include "Components/EquipComponent.h"
#include "GameFramework/Character.h"

UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UActionComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
}

void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UActionComponent::MouseL()
{
	UEquipComponent* Equip= OwnerCharacter->GetComponentByClass<UEquipComponent>();
	if (!Equip) return;
	Equip->WeaponL();
}

void UActionComponent::MouseR()
{
}

void UActionComponent::Num1()
{
	UEquipComponent* Equip = OwnerCharacter->GetComponentByClass<UEquipComponent>();
	if (!Equip) return;
	 Equip->SelectWeapon(0);
}

void UActionComponent::Num2()
{
	UEquipComponent* Equip = OwnerCharacter->GetComponentByClass<UEquipComponent>();
	if (!Equip) return;
	Equip->SelectWeapon(1);
}

void UActionComponent::SetActionMode(EActionType InNewType)
{
	EActionType prevType = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prevType, InNewType);
}

void UActionComponent::SetUnarmed()
{
	SetActionMode(EActionType::Unarmed);
}

void UActionComponent::SetAssassin()
{
	SetActionMode(EActionType::Assassin);
}

void UActionComponent::SetKanata()
{
	SetActionMode(EActionType::Kanata);
}

