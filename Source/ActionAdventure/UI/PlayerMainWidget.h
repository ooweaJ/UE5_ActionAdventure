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
	FORCEINLINE UUI_UserStatus* GetPlayerStatus() { return UserStatus; }

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUI_UserStatus* BossHPBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUI_UserStatus* UserStatus;
	
};
