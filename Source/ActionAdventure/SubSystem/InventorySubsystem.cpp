#include "SubSystem/InventorySubsystem.h"
#include "SubSystem/DataSubsystem.h"

void UInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UInventorySubsystem::Deinitialize()
{
}

void UInventorySubsystem::Save(URPGSaveGame* SaveGame)
{
}

void UInventorySubsystem::Load(ARPGPlayerController* Controller, URPGSaveGame* SaveGame)
{
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

void UInventorySubsystem::UnEquipWeapon(UInventoryUserWidget* Widget)
{
}

bool UInventorySubsystem::AddItem(const FName& InKey)
{
	return false;
}

bool UInventorySubsystem::MoveItemToInventory(TSharedPtr<FItemData>& InItem)
{
	return false;
}

void UInventorySubsystem::UseItem(UInventoryUserWidget* Widget, uint32 InIndex)
{
}
