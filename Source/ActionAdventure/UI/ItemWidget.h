#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "ItemWidget.generated.h"

DECLARE_DELEGATE_OneParam(FOnInvenButtonEvent, UItemWidget* /*Widget*/);

UCLASS()
class ACTIONADVENTURE_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnItemBtnHovered();
	UFUNCTION()
	void OnItemBtnClicked();

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ItemBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ItemImage;

	uint32 ItemIndex = (uint32)-1;

	FOnInvenButtonEvent ItemBtnHovered;
	FOnInvenButtonEvent ItemBtnClicked;

};
