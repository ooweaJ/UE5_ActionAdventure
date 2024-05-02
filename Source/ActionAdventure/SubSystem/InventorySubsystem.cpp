#include "SubSystem/InventorySubsystem.h"
#include "SubSystem/DataSubsystem.h"
#include "UI/InventoryWidget.h"
#include "UI/EquipWindowWidget.h"
#include "Characters/Controller/CPlayerController.h"
#include "Components/EquipComponent.h"

void UInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UInventorySubsystem::Deinitialize()
{
}

void UInventorySubsystem::Save(URPGSaveGame* SaveGame)
{
}

void UInventorySubsystem::Load(ACPlayerController* Controller, URPGSaveGame* SaveGame)
{
}

void UInventorySubsystem::SetInventory(UInventoryWidget* Widget)
{
	InvenWidget = Widget;

}

void UInventorySubsystem::SetEquipWindow(UEquipWindowWidget* Widget)
{
	EquipWidget = Widget;
}

void UInventorySubsystem::MakeInventory()
{
	DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	Inventory.SetNum(MaxInvenSize, false);

}

void UInventorySubsystem::ClearInventory()
{
	Inventory.Empty();
}

bool UInventorySubsystem::AddItem(const FName& InKey)
{
	FItemData* Data = DataSubsystem->FindItemData(InKey);
	if (!Data)
	{
		return false;
	}
	FItemData* NewItemData = new FItemData(*Data);
	return MoveItemToInventory(NewItemData);
}

bool UInventorySubsystem::AddItem(FItemData* InData)
{
	FItemData* NewItemData = new FItemData(*InData);
	return MoveItemToInventory(NewItemData);
}

bool UInventorySubsystem::MoveItemToInventory(FItemData* InItem)
{
	for (uint32 i = 0; i < MaxInvenSize; ++i)
	{
		FItemData* ItemData = Inventory[i];
		if (ItemData == nullptr) { continue; }
		if (ItemData->ItemClass != InItem->ItemClass) continue;

		if (ItemData->MaxBundleCount > ItemData->CurrentBundleCount)
		{
			++ItemData->CurrentBundleCount;
			return true;
		}
	}

	bool bAdded = false;
	for (uint32 i = 0; i < MaxInvenSize; ++i)
	{
		if (Inventory[i] == nullptr)
		{
			Inventory[i] = InItem;
			bAdded = true;
			break;
		}
	}

	InItem = nullptr;

	return bAdded;
}

void UInventorySubsystem::UseItem(UInventoryWidget* Widget, uint32 InIndex)
{
	FItemData* ItemData = Inventory[InIndex];
	if (!ItemData) { return; }

	ACPlayerController* PlayerController = Cast<ACPlayerController>(Widget->GetOwningPlayer());
	if (!PlayerController) return;

	UEquipComponent* equip = PlayerController->GetPawn()->GetComponentByClass<UEquipComponent>();
	if (!equip) return;

	bool bcanUse = equip->AddItem(Inventory[InIndex]);

	if (bcanUse)
	{
		--ItemData->CurrentBundleCount;

		if (ItemData->CurrentBundleCount == 0)
		{
			++ItemData->CurrentBundleCount;
			Inventory[InIndex] = nullptr;
		}
	}
	

	InvenWidget->FlushInven();
	EquipWidget->FlushEquip();

}

bool UInventorySubsystem::MoveItemToEquip(TSharedPtr<FItemData>& InItem)
{
	for (uint32 i = 0; i < MaxEquipSize; ++i)
	{
		TSharedPtr<FItemData> ItemData = Equipment[i];
		if (ItemData == nullptr) { continue; }
		if (ItemData->ItemName != InItem->ItemName) { continue; }

		if (ItemData->MaxBundleCount > ItemData->CurrentBundleCount)
		{
			++ItemData->CurrentBundleCount;
			return true;
		}
	}

	bool bAdded = false;
	for (uint32 i = 0; i < MaxEquipSize; ++i)
	{
		if (Equipment[i] == nullptr)
		{
			Equipment[i] = InItem;
			bAdded = true;
			break;
		}
	}

	InItem = nullptr;


	return bAdded;
}

void UInventorySubsystem::UseItemEquip(UEquipWindowWidget* Widget, FItemData* InData)
{
	AddItem(InData);
	InvenWidget->FlushInven();
}
