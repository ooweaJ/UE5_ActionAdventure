#include "UI/UI_Store.h"
#include "SubSystem/DataSubsystem.h"
#include "SubSystem/InventorySubsystem.h"
#include "Engine/DataTable.h"
#include "Data/Item/ItemData.h"
#include "UI/StoreItemWidget.h"
#include "UI/InventoryWidget.h"

UUI_Store::UUI_Store(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> findclass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/UI_StoreItem.UI_StoreItem_C'"));
	if (findclass.Succeeded())
		ItemSlot = findclass.Class;
}

void UUI_Store::NativeConstruct()
{
	UDataSubsystem* DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	UDataTable* table = DataSubsystem->GetItemData();

	TArray<FItemData*> datas;
	table->GetAllRows<FItemData>("", datas);

	ItemDatas.SetNum(datas.Num());

	for (int32 i = 1; i < datas.Num(); ++i)
	{
	
		UStoreItemWidget* Widget = CreateWidget<UStoreItemWidget>(this, ItemSlot);

		Widget->StoreBtnClicked.BindUFunction(this, TEXT("OnItemBtnClicked"));
		Widget->ItemIndex = i;
		UTexture2D* Texture = datas[i]->ItemImage;
		Widget->ItemImage->SetBrushFromTexture(Texture, false);
		Widget->ItemDesc->SetText(datas[i]->ItemDesc);

		Items.Add(Widget);
		StoreBox->AddChild(Widget);

		ItemDatas[i] = datas[i];
	}
	ExitBtn->OnClicked.AddDynamic(this, &ThisClass::Exit);

}

void UUI_Store::OnItemBtnClicked(UStoreItemWidget* InWidget)
{
	int32 index = InWidget->ItemIndex;
	ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	UInventorySubsystem* InventorySubsystem = ULocalPlayer::GetSubsystem<UInventorySubsystem>(LocalPlayer);
	FItemData* NewItemData =  new FItemData(*ItemDatas[index]);
	InventorySubsystem->AddItem(NewItemData);
	InventorySubsystem->InvenWidget->FlushInven();
}

void UUI_Store::Exit()
{
	SetVisibility(ESlateVisibility::Hidden);
}
