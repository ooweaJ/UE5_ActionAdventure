#include "Components/EquipComponent.h"
#include "Components/StateComponent.h"
#include "SubSystem/DataSubsystem.h"
#include "GameFramework/Character.h"
#include "Data/ActionData/ActionDataTableRow.h"

UEquipComponent::UEquipComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	UDataSubsystem* DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();

	{
		const FWeaponDataTableRow* Weaponclass = DataSubsystem->FindWeaponData(TEXT("Fist"));
		AddWeapons(Weaponclass->WeaponClass);
	}
	{
		const FWeaponDataTableRow* Weaponclass = DataSubsystem->FindWeaponData(TEXT("Assassin"));
		AddWeapons(Weaponclass->WeaponClass);
	}
	{
		const FWeaponDataTableRow* Weaponclass = DataSubsystem->FindWeaponData(TEXT("Kanata"));
		AddWeapons(Weaponclass->WeaponClass);
	}
	State = Cast<UStateComponent>(OwnerCharacter->GetComponentByClass<UStateComponent>());

	CurrentWeapon = DefaultWeapon;
}

void UEquipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEquipComponent::WeaponL()
{
	CurrentWeapon->Attack();
}

void UEquipComponent::SelectWeapon(int32 WeaponNum)
{
	if (!State->IsIdleMode()) return;
	if (CurrentWeapon == EquipWeapons[WeaponNum])
	{
		CurrentWeapon->UnEquipWeapon();
		CurrentWeapon = DefaultWeapon;
		return;
	}
	else
	{
		if(CurrentWeapon != DefaultWeapon)
			CurrentWeapon->UnEquipWeapon();

		CurrentWeapon = EquipWeapons[WeaponNum];
		CurrentWeapon->EquipWeapon();
	}
}

void UEquipComponent::AddWeapons(TSubclassOf<AWeapon> EquipWeapon)
{
	if (EquipWeapons.Num() >= 8) return;
	UDataSubsystem* DataSubsystem = OwnerCharacter->GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	AWeapon* weapon = OwnerCharacter->GetWorld()->SpawnActorDeferred<AWeapon>(EquipWeapon, OwnerCharacter->GetActorTransform(), OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	weapon->SetWeaponData(OwnerCharacter, DataSubsystem->FindActionData(weapon->KeyValue));
	weapon->FinishSpawning(OwnerCharacter->GetActorTransform(), true);

	if (weapon->GetActiontype() == EActionType::Unarmed)
		DefaultWeapon = weapon;
	else
		EquipWeapons.Add(weapon);
}

