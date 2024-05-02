#include "UI/EquipItemWidget.h"

void UEquipItemWidget::NativeOnInitialized()
{
	Itembtn->OnClicked.AddDynamic(this, &ThisClass::OnItemBtnClicked);
}

void UEquipItemWidget::OnItemBtnClicked()
{
	if (EquipBtnClicked.IsBound())
	{
		EquipBtnClicked.Execute(this);
	}
}
