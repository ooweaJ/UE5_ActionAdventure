#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "EquipItemWidget.generated.h"

DECLARE_DELEGATE_OneParam(FOnEquipButtonEvent, UEquipItemWidget* /*Widget*/);

UCLASS()
class ACTIONADVENTURE_API UEquipItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnItemBtnClicked();

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* frame;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Itembtn;

	bool bSelect = false;

	uint32 ItemIndex = (uint32)-1;

	FOnEquipButtonEvent EquipBtnClicked;
};
