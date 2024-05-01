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

	void FlushInven();

	UFUNCTION()
	void OnItemBtnClicked(UItemWidget* InWidget);
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUniformGridPanel* StorePanel;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ItemInfo;

	TArray<struct FItemData*> ItemDatas;
	UPROPERTY()
	TArray<class UItemWidget*> Items;
};
