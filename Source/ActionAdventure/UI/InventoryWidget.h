#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "InventoryWidget.generated.h"

UCLASS()
class ACTIONADVENTURE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	friend class UInventorySubsystem;
	friend class UUI_Store;
public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void FlushInven();

	UFUNCTION()
	void Exit();

	UFUNCTION()
	void OnItemBtnClicked(UItemWidget* InWidget);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUniformGridPanel* InventoryPanel;

	int32 InvenSize = 0;

	UInventorySubsystem* InventorySubsystem;

	UPROPERTY()
	TArray<class UItemWidget*> Items;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Exitbtn;

 private:
	TSubclassOf<class UUserWidget> ItemSlot;

	UTexture2D* DefaultTexture;
};
