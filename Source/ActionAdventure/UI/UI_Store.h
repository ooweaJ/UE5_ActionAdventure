#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "UI_Store.generated.h"

UCLASS()
class ACTIONADVENTURE_API UUI_Store : public UUserWidget
{
	GENERATED_BODY()

	friend class UInventorySubsystem;

protected:
	virtual void NativeConstruct() override;
	UUI_Store(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void OnItemBtnClicked(class UStoreItemWidget* InWidget);

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget* StoreBox;

	TArray<struct FItemData*> ItemDatas;

	UPROPERTY()
	TArray<class UStoreItemWidget*> Items;

private:
	TSubclassOf<class UUserWidget> ItemSlot;
};
