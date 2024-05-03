// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemWidget.h"

void UItemWidget::NativeOnInitialized()
{
	ItemBtn->OnHovered.AddDynamic(this, &ThisClass::OnItemBtnHovered);
	ItemBtn->OnClicked.AddDynamic(this, &ThisClass::OnItemBtnClicked);
}

void UItemWidget::OnItemBtnHovered()
{
	if (ItemBtnHovered.IsBound())
	{
		ItemBtnHovered.Execute(this);
	}
}

void UItemWidget::OnItemBtnClicked()
{
	if (ItemBtnClicked.IsBound())
	{
		ItemBtnClicked.Execute(this);
	}
}
