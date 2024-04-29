// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/DataSubsystem.h"

UDataSubsystem::UDataSubsystem()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/_dev/Data/WeaponData.WeaponData'") };
		ensure(Asset.Object);
		ActionDataTable = Asset.Object;
	}

	{
	/*	static ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/_dev/Data/WeaponClassData.WeaponClassData'") };
		ensure(Asset.Object);
		ItemDataTable = Asset.Object;*/
	}
}

const FActionData* UDataSubsystem::FindActionData(const FName& InKey)
{
	FActionData* Row = ActionDataTable->FindRow<FActionData>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}

const FItemData* UDataSubsystem::FindItemData(const FName& InKey)
{
	FItemData* Row = ItemDataTable->FindRow<FItemData>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}

