#include "Components/EquipComponent.h"
#include "Components/StateComponent.h"
#include "SubSystem/DataSubsystem.h"
#include "GameFramework/Character.h"
#include "Data/ActionData/ActionDataTableRow.h"
#include "Actors/Weapon/Attachment.h"

UEquipComponent::UEquipComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	EquipItems.SetNum(10, false);
}

void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	UDataSubsystem* DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();

	//{
	//	const FItemData* ItemData = DataSubsystem->FindItemData(TEXT("Fist"));
	//	AddItem(ItemData->ItemClass);
	//}
	//{
	//	const FItemData* ItemData = DataSubsystem->FindItemData(TEXT("Assassin"));
	//	AddItem(ItemData->ItemClass);
	//}
	//{
	//	const FItemData* ItemData = DataSubsystem->FindItemData(TEXT("Katana"));
	//	AddItem(ItemData->ItemClass);
	//}
	//{
	//	const FItemData* ItemData = DataSubsystem->FindItemData(TEXT("Rifle"));
	//	AddItem(ItemData->ItemClass);
	//}

	//State = Cast<UStateComponent>(OwnerCharacter->GetComponentByClass<UStateComponent>());

	//CurrentItem = DefaultWeapon;
}

void UEquipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEquipComponent::WeaponL()
{
	CurrentWeapon->MouseL();
}

void UEquipComponent::WeaponR()
{
	CurrentWeapon->MouseR();
}

void UEquipComponent::OffWeaponR()
{
	CurrentWeapon->OffMouseR();
}

void UEquipComponent::SelectWeapon(int32 WeaponNum)
{
	if (!State->IsIdleMode()) return;
	if (CurrentWeapon == EquipWeapons[WeaponNum])
	{
		CurrentWeapon->UnEquipItem();
		CurrentWeapon = DefaultWeapon;
		return;
	}
	else
	{
		if(CurrentWeapon != DefaultWeapon)
			CurrentWeapon->UnEquipItem();

		CurrentWeapon = EquipWeapons[WeaponNum];
		CurrentWeapon->EquipItem();
	}
}

void UEquipComponent::AddItem(TSubclassOf<AItem> EquipItem)
{
	/*if (EquipWeapons.Num() >= 8) return;
	UDataSubsystem* DataSubsystem = OwnerCharacter->GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	AWeapon* weapon = Cast<AWeapon>(OwnerCharacter->GetWorld()->SpawnActorDeferred<AItem>(EquipItem, OwnerCharacter->GetActorTransform(), OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
	weapon->SetWeaponData(OwnerCharacter, DataSubsystem->FindActionData(weapon->KeyValue));
	weapon->FinishSpawning(OwnerCharacter->GetActorTransform(), true);

	if (weapon->GetActiontype() == EActionType::Unarmed)
		DefaultWeapon = weapon;
	else
		EquipWeapons.Add(weapon);*/
}

void UEquipComponent::EndDead()
{
	DefaultWeapon->Attachment->Destroy();
	DefaultWeapon->Destroy();
	for (AWeapon* Actor : EquipWeapons)
	{
		Actor->Attachment->Destroy();
		Actor->Destroy();
	}
}

