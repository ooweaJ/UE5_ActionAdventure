#include "UI/StoreItemWidget.h"

void UStoreItemWidget::NativeOnInitialized()
{
	StoreBtn->OnHovered.AddDynamic(this, &ThisClass::OnItemBtnHovered);
	StoreBtn->OnClicked.AddDynamic(this, &ThisClass::OnItemBtnClicked);
}

void UStoreItemWidget::OnItemBtnHovered()
{
	if (StoreBtnHovered.IsBound())
	{
		StoreBtnHovered.Execute(this);
	}
}

void UStoreItemWidget::OnItemBtnClicked()
{
	if (StoreBtnClicked.IsBound())
	{
		StoreBtnClicked.Execute(this);
	}
}
