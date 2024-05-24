#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMainWidget.generated.h"

class UUI_UserStatus;

UCLASS()
class ACTIONADVENTURE_API UPlayerMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	FORCEINLINE UUI_UserStatus* GetBossHPBar() { return BossHPBar; }
	FORCEINLINE UUI_UserStatus* GetBossSkillBar() { return BossSkillBar; }
	FORCEINLINE UUI_UserStatus* GetPlayerStatus() { return UserStatus; }

	FORCEINLINE void OnAim() { Aim->SetVisibility(ESlateVisibility::Visible); }
	FORCEINLINE void OffAim() { Aim->SetVisibility(ESlateVisibility::Hidden); }

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUI_UserStatus* BossHPBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUI_UserStatus* UserStatus;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUI_UserStatus* BossSkillBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUserWidget* Aim;
};
