#include "Ui/PlayerMainWidget.h"
#include "UI/UI_UserStatus.h"
void UPlayerMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BossHPBar->SetVisibility(ESlateVisibility::Hidden);
	BossSkillBar->SetVisibility(ESlateVisibility::Hidden);
}
