// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Actors/Weapon/Weapon.h"
#include "DataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONADVENTURE_API UDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UDataSubsystem();

public:
	FORCEINLINE UDataTable* GetItemData() { return ItemDataTable; }

	const FItemActionData* FindActionData(const FName& InKey);
	FItemData* FindItemData(const FName& InKey);

protected:
	UPROPERTY()
	UDataTable* ActionDataTable;

	UPROPERTY()
	UDataTable* ItemDataTable;
};
