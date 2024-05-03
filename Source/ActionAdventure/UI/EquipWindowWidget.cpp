#include "UI/EquipWindowWidget.h"
#include "UI/EquipItemWidget.h"
#include "UI/ItemWidget.h"
#include "Components/EquipComponent.h"
#include "SubSystem/InventorySubsystem.h"

UEquipWindowWidget::UEquipWindowWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> findclass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/UI_EquipItem.UI_EquipItem_C'"));
	if (findclass.Succeeded())
		EquipItem = findclass.Class;

	ConstructorHelpers::FObjectFinder<UTexture2D> object(TEXT("/Script/Engine.Texture2D'/Game/GUI_Parts/Gui_parts/Mini_background.Mini_background'"));
	if (object.Succeeded())
		DefaultTexture = object.Object;
}

void UEquipWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	InventorySubsystem = ULocalPlayer::GetSubsystem<UInventorySubsystem>(LocalPlayer);
	InventorySubsystem->SetEquipWindow(this);

	UEquipComponent* equip = GetOwningPlayer()->GetPawn()->GetComponentByClass<UEquipComponent>();
	if (!equip) return;
	Equip = equip;


	for (int32 i = 0; i < EquipSize; ++i)
	{
		UEquipItemWidget* Widget =CreateWidget<UEquipItemWidget>(this, EquipItem);
		if (!Widget) return;

		Widget->EquipBtnClicked.BindUFunction(this, TEXT("OnItemBtnClicked"));
		Widget->ItemIndex = i;
		Items.Add(Widget);
		EquipPanel->AddChildToUniformGrid(Widget, 0, i);
	}
	
	FlushEquip();
}

void UEquipWindowWidget::OnItemBtnClicked(UEquipItemWidget* InWidget)
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

void UEquipWindowWidget::FlushEquip()
{
	for (int32 i = 0; i < EquipSize; ++i)
	{
		if (Equip->ItemDatas[i] == nullptr)
		{
			Items[i]->ItemImage->SetBrushFromTexture(DefaultTexture, false);
			continue;
		}

		UTexture2D* Texture = Equip->ItemDatas[i]->ItemImage;
		Items[i]->ItemImage->SetBrushFromTexture(Texture, false);
	}
}
