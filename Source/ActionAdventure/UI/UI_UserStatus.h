#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "UI_UserStatus.generated.h"

UCLASS()
class ACTIONADVENTURE_API UUI_UserStatus : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHP(const float CurrentHP, const float MaxHP);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* HPBar = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* HPSecond = nullptr;

private:
	float TargetPercent;
};
