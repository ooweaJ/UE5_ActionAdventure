#include "SubSystem/InventorySubsystem.h"

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
}

void UInventorySubsystem::ClearInventory()
{
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
