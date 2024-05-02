#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "StoreItemWidget.generated.h"

DECLARE_DELEGATE_OneParam(FOnStoreButtonEvent, UStoreItemWidget* /*Widget*/);

UCLASS()
class ACTIONADVENTURE_API UStoreItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnItemBtnHovered();
	UFUNCTION()
	void OnItemBtnClicked();

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* StoreBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ItemDesc;

	uint32 ItemIndex = (uint32)-1;

	FOnStoreButtonEvent StoreBtnHovered;
	FOnStoreButtonEvent StoreBtnClicked;
};
