#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "EquipWindowWidget.generated.h"

UCLASS()
class ACTIONADVENTURE_API UEquipWindowWidget : public UUserWidget
{
	GENERATED_BODY()
	
	friend class UInventorySubsystem;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnItemBtnClicked(UItemWidget* InWidget);

	void FlushEquip();
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUniformGridPanel* EquipPanel;

	UPROPERTY()
	TArray<class UItemWidget*> Items;
private:
	int32 EquipSize = 8; 

	class UEquipComponent* Equip;

	UInventorySubsystem* InventorySubsystem;
};
