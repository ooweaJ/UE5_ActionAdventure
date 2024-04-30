#include "UI/InventoryWidget.h"
#include "SubSystem/InventorySubsystem.h"
#include "UI/ItemWidget.h"
#include "Components/GridPanel.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	InventorySubsystem = ULocalPlayer::GetSubsystem<UInventorySubsystem>(LocalPlayer);
	InventorySubsystem->SetInventory(this);
	InvenSize = InventorySubsystem->Inventory.Num();

	// 게임에서 참조된 적이 없어서 로드가 안됨
	LoadClass<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/UI_Item.UI_Item_C'"),
		nullptr, LOAD_None, nullptr);
	UClass* InventoryItemWidgetClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/UI_Item.UI_Item_C'"));

	int32 Col = 6;
	int32 Row = InvenSize / Col;

	for (int32 i = 0; i < Row; ++i)
	{
		for (int32 k = 0; k < Col; ++k)
		{
			UItemWidget* Widget = Cast<UItemWidget>(CreateWidget(this, InventoryItemWidgetClass));
			ensure(Widget);

			Widget->ItemBtnClicked.BindUFunction(this, TEXT("OnItemBtnClicked"));
			Widget->ItemIndex = k + i * Col;
			Items.Add(Widget);
			InventoryPanel->AddChildToUniformGrid(Widget, i, k);
		}
	}
	FlushInven();
}

void UInventoryWidget::NativeDestruct()
{
}

void UInventoryWidget::FlushInven()
{
	for (int32 i = 0; i < InvenSize; ++i)
	{
		if (InventorySubsystem->Inventory[i] == nullptr)
		{
			Items[i]->ItemImage->SetBrushFromTexture(nullptr, false);
			continue;
		}

		UTexture2D* Texture = InventorySubsystem->Inventory[i]->ItemImage;
		Items[i]->ItemImage->SetBrushFromTexture(Texture, false);
	}
}

void UInventoryWidget::OnItemBtnClicked(UItemWidget* InWidget)
{
	const uint32 Index = InWidget->ItemIndex;
	FItemData* ItemData = InventorySubsystem->Inventory[Index];
	if (ItemData)
	{
		InventorySubsystem->UseItem(this, Index);
	}
}
