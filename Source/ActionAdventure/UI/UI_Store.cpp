#include "UI/UI_Store.h"
#include "SubSystem/DataSubsystem.h"
#include "SubSystem/InventorySubsystem.h"
#include "Engine/DataTable.h"
#include "Data/Item/ItemData.h"
#include "UI/ItemWidget.h"

void UUI_Store::NativeConstruct()
{
	//UDataSubsystem* DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	//UDataTable* table = DataSubsystem->GetItemData();

	//TArray<FItemData*> datas;
	//table->GetAllRows<FItemData>("", datas);
	//
	//LoadClass<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/UI_Item.UI_Item_C'"),
	//	nullptr, LOAD_None, nullptr);
	//UClass* InventoryItemWidgetClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/UI_Item.UI_Item_C'"));


	//for (int32 i = 0; i < datas.Num() - 1; ++i)
	//{
	//
	//	UItemWidget* Widget = Cast<UItemWidget>(CreateWidget(this, InventoryItemWidgetClass));
	//	ensure(Widget);

	//	Widget->ItemBtnClicked.BindUFunction(this, TEXT("OnItemBtnClicked"));
	//	Widget->ItemIndex = i;
	//	Items.Add(Widget);
	//	StorePanel->AddChildToUniformGrid(Widget, i, 0);

	//	ItemDatas[i] = datas[i+1];

	//	UTexture2D* Texture = datas[i+1]->ItemImage;
	//	Items[i]->ItemImage->SetBrushFromTexture(Texture, false);
	//	Items[i]->ItemName->SetText(FText::FromName(datas[i + 1]->ItemName));
	//}
}

void UUI_Store::FlushInven()
{

}

void UUI_Store::OnItemBtnClicked(UItemWidget* InWidget)
{
	ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	UInventorySubsystem* InventorySubsystem = ULocalPlayer::GetSubsystem<UInventorySubsystem>(LocalPlayer);
	const uint32 Index = InWidget->ItemIndex;
	InventorySubsystem->AddItem(ItemDatas[Index]);
}
