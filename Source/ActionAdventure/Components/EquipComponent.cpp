#include "Components/EquipComponent.h"
#include "Components/StateComponent.h"
#include "SubSystem/DataSubsystem.h"
#include "GameFramework/Character.h"
#include "Data/ActionData/ActionDataTableRow.h"
#include "Actors/Weapon/Attachment.h"
#include "Characters/Players/CPlayer.h"

UEquipComponent::UEquipComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	ItemDatas.SetNum(8, false);
	EquipItems.SetNum(8, false);
}

void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	{
		OwnerCharacter = Cast<ACharacter>(GetOwner());
		State = Cast<UStateComponent>(OwnerCharacter->GetComponentByClass<UStateComponent>());
	}

	if(Cast<ACPlayer>(OwnerCharacter))
	{
		UDataSubsystem* DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
		FItemData* FistData = DataSubsystem->FindItemData("Fist");
		if (FistData == nullptr) return;

		AItem* Item = Cast<AItem>(OwnerCharacter->GetWorld()->SpawnActorDeferred<AItem>(FistData->ItemClass, OwnerCharacter->GetActorTransform(), OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
		Item->SetItemData(OwnerCharacter, DataSubsystem->FindActionData(Item->KeyValue));
		Item->FinishSpawning(OwnerCharacter->GetActorTransform(), true);

		DefaultWeapon = Item;
		CurrentItem = DefaultWeapon;
	}

}

void UEquipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEquipComponent::WeaponL()
{
	if(CurrentItem != nullptr)
		CurrentItem->MouseL();
}

void UEquipComponent::WeaponR()
{
	if (CurrentItem != nullptr)
		CurrentItem->MouseR();
}

void UEquipComponent::OffWeaponR()
{
	if (CurrentItem != nullptr)
		CurrentItem->OffMouseR();
}

void UEquipComponent::SelectWeapon(int32 WeaponNum)
{
	if (!State->IsIdleMode()) return;
	if (EquipItems[WeaponNum] == nullptr) return;
	if (CurrentItem == EquipItems[WeaponNum])
	{
		CurrentItem->UnEquipItem();
		CurrentItem = DefaultWeapon;
		return;
	}
	else
	{
		if(CurrentItem != DefaultWeapon)
			CurrentItem->UnEquipItem();

		CurrentItem = EquipItems[WeaponNum];
		CurrentItem->EquipItem();
	}
}

bool UEquipComponent::AddItem(FItemData* ItemData)
{
	if (!CanIsPool()) return false;
	AddData(ItemData);
	
	EquipItem(ItemData->ItemClass);
	return true;
}

void UEquipComponent::EquipItem(TSubclassOf<AItem> EquipItem)
{
	UDataSubsystem* DataSubsystem = OwnerCharacter->GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	AItem* Item = Cast<AItem>(OwnerCharacter->GetWorld()->SpawnActorDeferred<AItem>(EquipItem, OwnerCharacter->GetActorTransform(), OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));

	Item->SetItemData(OwnerCharacter, DataSubsystem->FindActionData(Item->KeyValue));
	Item->FinishSpawning(OwnerCharacter->GetActorTransform(), true);


	for (int32 i = 0; i < EquipItems.Num(); ++i)
	{
		if (EquipItems[i] == nullptr)
		{
			EquipItems[i] = Item;
			break;
		}
	}
}

void UEquipComponent::UnEquipItem(int32 index)
{
	EquipItems[index]->Attachment->Destroy();
	EquipItems[index]->Destroy();
	EquipItems[index] = nullptr;
	CurrentItem = DefaultWeapon;
}

void UEquipComponent::EndDead()
{
	/*DefaultWeapon->Attachment->Destroy();
	DefaultWeapon->Destroy();
	if (EquipItems.Num() == 0) return;
	for (AItem* Actor : EquipItems)
	{
		Actor->Attachment->Destroy();
		Actor->Destroy();
	}*/
}

void UEquipComponent::AddData(FItemData* InData)
{
	for (int32 i = 0; i < ItemDatas.Num(); ++i)
	{
		if (ItemDatas[i] == nullptr)
		{
			ItemDatas[i] = InData;
			break;
		}
	}
}

void UEquipComponent::AIRandomWeapon()
{
	int32 randomint = FMath::RandRange(0, (int32)EWeapon::Max -1);

	UDataSubsystem* DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	FItemData* FindData = DataSubsystem->FindItemData(Key[randomint]);
	if (FindData == nullptr)
	{
		return;
	}

	AItem* Item = Cast<AItem>(OwnerCharacter->GetWorld()->SpawnActorDeferred<AItem>(FindData->ItemClass, OwnerCharacter->GetActorTransform(), OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
	Item->SetItemData(OwnerCharacter, DataSubsystem->FindActionData(Item->KeyValue));
	Item->FinishSpawning(OwnerCharacter->GetActorTransform(), true);
	DefaultWeapon = Item;
	CurrentItem = DefaultWeapon;
}

void UEquipComponent::AICombat()
{
	CurrentItem->EquipItem();
}

bool UEquipComponent::CanIsPool()
{
	bool bCanispool = false;
	for (int32 i = 0; i < ItemDatas.Num(); ++i)
	{
		if (ItemDatas[i] == nullptr)
			bCanispool = true;
	}
	
	return bCanispool;
}

