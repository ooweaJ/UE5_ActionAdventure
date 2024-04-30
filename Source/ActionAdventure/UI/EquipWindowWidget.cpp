#include "UI/EquipWindowWidget.h"
#include "UI/ItemWidget.h"
#include "Components/EquipComponent.h"
#include "SubSystem/InventorySubsystem.h"

void UEquipWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	InventorySubsystem = ULocalPlayer::GetSubsystem<UInventorySubsystem>(LocalPlayer);
	InventorySubsystem->SetEquipWindow(this);

	UEquipComponent* equip = GetOwningPlayer()->GetPawn()->GetComponentByClass<UEquipComponent>();
	if (!equip) return;
	Equip = equip;

	LoadClass<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/UI_Item.UI_Item_C'"),
		nullptr, LOAD_None, nullptr);
	UClass* ItemWidgetClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/UI_Item.UI_Item_C'"));

	for (int32 i = 0; i < EquipSize; ++i)
	{
		UItemWidget* Widget = Cast<UItemWidget>(CreateWidget(this, ItemWidgetClass));
		ensure(Widget);

		//Widget->ItemBtnClicked.BindUFunction(this, TEXT("OnItemBtnClicked"));

		Widget->ItemIndex = i;
		Widget->ItemBtnClicked.BindUFunction(this, TEXT("OnItemBtnClicked"));
		Items.Add(Widget);
		EquipPanel->AddChildToUniformGrid(Widget, i);
	}

	FlushEquip();
}
void UEquipWindowWidget::OnItemBtnClicked(UItemWidget* InWidget)
{
	const uint32 Index = InWidget->ItemIndex;
	FItemData* ItemData = Equip->ItemDatas[Index];
	if (ItemData)
	{
		InventorySubsystem->UseItemEquip(this, ItemData);
		Equip->ItemDatas[Index] = nullptr;
		Equip->UnEquipItem(Index);
		FlushEquip();
	}

}
//
//void UEquipWindowWidget::PostLoad()
//{
//	Super::PostLoad();
//
//	UEquipComponent* equip = GetOwningPlayer()->GetPawn()->GetComponentByClass<UEquipComponent>();
//
//	if (!equip) return;
//	Equip = equip;
//
//	LoadClass<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/UI_Item.UI_Item_C'"),
//		nullptr, LOAD_None, nullptr);
//	UClass* ItemWidgetClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/UI_Item.UI_Item_C'"));
//
//	for (int32 i = 0; i < EquipSize; ++i)
//	{
//		UItemWidget* Widget = Cast<UItemWidget>(CreateWidget(this, ItemWidgetClass));
//		ensure(Widget);
//
//		//Widget->ItemBtnClicked.BindUFunction(this, TEXT("OnItemBtnClicked"));
//		Widget->ItemIndex = i;
//		Items.Add(Widget);
//		EquipPanel->AddChildToUniformGrid(Widget, i);
//	}
//
//	FlushEquip();
//}



void UEquipWindowWidget::FlushEquip()
{
	for (int32 i = 0; i < EquipSize; ++i)
	{
		if (Equip->ItemDatas[i] == nullptr)
		{
			Items[i]->ItemImage->SetBrushFromTexture(nullptr, false);
			continue;
		}

		UTexture2D* Texture = Equip->ItemDatas[i]->ItemImage;
		Items[i]->ItemImage->SetBrushFromTexture(Texture, false);
	}
}
