#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "InventoryWidget.generated.h"

UCLASS()
class ACTIONADVENTURE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	friend class UInventorySubsystem;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void FlushInven();

	UFUNCTION()
	void OnItemBtnClicked(UItemWidget* InWidget);

	UFUNCTION()
	void OnWeaponBtnClicked(UItemWidget* InWidget);

	UFUNCTION()
	void OnWeaponBtnHovered(UItemWidget* InWidget);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUniformGridPanel* InventoryPanel;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ItemDesc;
};
