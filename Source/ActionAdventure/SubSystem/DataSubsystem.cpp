#include "SubSystem/DataSubsystem.h"

UDataSubsystem::UDataSubsystem()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/_dev/Data/DT_ItmeActionData.DT_ItmeActionData'") };
		ensure(Asset.Object);
		ActionDataTable = Asset.Object;
	}

	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/_dev/Data/DT_ItemData.DT_ItemData'") };
		ensure(Asset.Object);
		ItemDataTable = Asset.Object;
	}
}

const FItemActionData* UDataSubsystem::FindActionData(const FName& InKey)
{
	FItemActionData* Row = ActionDataTable->FindRow<FItemActionData>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}

FItemData* UDataSubsystem::FindItemData(const FName& InKey)
{
	FItemData* Row = ItemDataTable->FindRow<FItemData>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}

