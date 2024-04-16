// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/DataSubsystem.h"

UDataSubsystem::UDataSubsystem()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/_dev/Characters/Players/WeaponData.WeaponData'") };
		ensure(Asset.Object);
		ActionDataTable = Asset.Object;
	}

	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/_dev/Characters/Players/WeaponClassData.WeaponClassData'") };
		ensure(Asset.Object);
		WeaponDataTable = Asset.Object;
	}
}

const FWeaponData* UDataSubsystem::FindActionData(const FName& InKey)
{
	FWeaponData* Row = ActionDataTable->FindRow<FWeaponData>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}

const FWeaponDataTableRow* UDataSubsystem::FindWeaponData(const FName& InKey)
{
	FWeaponDataTableRow* Row = WeaponDataTable->FindRow<FWeaponDataTableRow>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}
