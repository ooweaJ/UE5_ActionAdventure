// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "Data/Item/ItemData.h"
#include "InventorySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONADVENTURE_API UInventorySubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

	friend class UInventoryWidget;
	friend class ACPlayerController;
	friend class UEquipWindowWidget;
	friend class UUI_Store;
protected:
	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

	void Save(class URPGSaveGame* SaveGame);
	void Load(class ACPlayerController* Controller, class URPGSaveGame* SaveGame);

	void SetInventory(UInventoryWidget* Widget);
	void SetEquipWindow(UEquipWindowWidget* Widget);

	void MakeInventory();
	void ClearInventory();

	bool AddItem(const FName& InKey);
	bool AddItem(FItemData* InData);
	bool MoveItemToInventory(FItemData* InItem);
	void UseItem(class UInventoryWidget* Widget, uint32 InIndex);

	bool MoveItemToEquip(TSharedPtr<FItemData>& InItem);
	void UseItemEquip(class UEquipWindowWidget* Widget, FItemData* InData);
protected:
	const uint32 MaxInvenSize = 60;
	const uint32 MaxEquipSize = 8;
	TArray<FItemData*> Inventory;
	TArray<TSharedPtr<FItemData>> Equipment;

	UInventoryWidget* InvenWidget;
	UEquipWindowWidget* EquipWidget;

	class UDataSubsystem* DataSubsystem;
};
