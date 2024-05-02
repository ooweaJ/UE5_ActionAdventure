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

public:
	UEquipWindowWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnItemBtnClicked(UEquipItemWidget* InWidget);

	void FlushEquip();
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUniformGridPanel* EquipPanel;

	UPROPERTY()
	TArray<class UEquipItemWidget*> Items;
private:
	int32 EquipSize = 7; 

	class UEquipComponent* Equip;

	UInventorySubsystem* InventorySubsystem;

private:
	TSubclassOf<class UUserWidget> EquipItem;

	UTexture2D* DefaultTexture;
};
