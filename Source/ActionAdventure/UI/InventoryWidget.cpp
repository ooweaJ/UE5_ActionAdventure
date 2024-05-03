#include "UI/InventoryWidget.h"
#include "SubSystem/InventorySubsystem.h"
#include "UI/ItemWidget.h"
#include "Components/GridPanel.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> findclass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/UI_ItemSlot.UI_ItemSlot_C'"));
		if (findclass.Succeeded())
			ItemSlot = findclass.Class;

	ConstructorHelpers::FObjectFinder<UTexture2D> object(TEXT("/Script/Engine.Texture2D'/Game/GUI_Parts/Gui_parts/Mini_background.Mini_background'"));
	if (object.Succeeded())
		DefaultTexture = object.Object;
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	InventorySubsystem = ULocalPlayer::GetSubsystem<UInventorySubsystem>(LocalPlayer);
	InventorySubsystem->SetInventory(this);
	InvenSize = InventorySubsystem->Inventory.Num();

	int32 Col = 5;
	int32 Row = InvenSize / Col;

	for (int32 i = 0; i < Row; ++i)
	{
		for (int32 k = 0; k < Col; ++k)
		{
			UItemWidget* Widget = CreateWidget<UItemWidget>(this, ItemSlot);
			ensure(Widget);

			Widget->ItemBtnClicked.BindUFunction(this, TEXT("OnItemBtnClicked"));
			Widget->ItemIndex = k + i * Col;
			Items.Add(Widget);
			InventoryPanel->AddChildToUniformGrid(Widget, i, k);
		}
	}
	Exitbtn->OnClicked.AddDynamic(this, &ThisClass::Exit);
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
			Items[i]->Amount->SetText(FText::FromString(""));
			Items[i]->ItemImage->SetBrushFromTexture(DefaultTexture, false);
			continue;
		}

		UTexture2D* Texture = InventorySubsystem->Inventory[i]->ItemImage;
		Items[i]->ItemImage->SetBrushFromTexture(Texture, false);

		if (InventorySubsystem->Inventory[i]->CurrentBundleCount > 1)
		{
			FString amount = FString::FromInt(InventorySubsystem->Inventory[i]->CurrentBundleCount);
			Items[i]->Amount->SetText(FText::FromString(amount));
		}
		else
			Items[i]->Amount->SetText(FText::FromString(""));
	}
}

void UInventoryWidget::Exit()
{
	SetVisibility(ESlateVisibility::Hidden);
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
