// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/DataSubsystem.h"

UDataSubsystem::UDataSubsystem()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/_dev/Characters/Players/WeaponData.WeaponData'") };
		ensure(Asset.Object);
		ActionDataTable = Asset.Object;
	}
}

const FWeaponData* UDataSubsystem::FindActionData(const FName& InKey)
{
	FWeaponData* Row = ActionDataTable->FindRow<FWeaponData>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}
