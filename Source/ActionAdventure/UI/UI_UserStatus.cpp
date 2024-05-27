#include "UI/UI_UserStatus.h"

void UUI_UserStatus::SetHP(const float CurrentHP, const float MaxHP)
{
    if (FMath::IsNearlyZero(MaxHP))
    {
        ensure(false);
    }
    const float Percent = CurrentHP / MaxHP;

    // HPBar는 바로 설정
    HPBar->SetPercent(Percent);

    // HPSecond는 보간을 통해 부드럽게 변경
    TargetPercent = Percent;
}

void UUI_UserStatus::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    // HPSecond를 보간하여 부드럽게 변경
    float CurrentPercent = HPSecond->Percent;
    float InterpolatedPercent = FMath::FInterpTo(CurrentPercent, TargetPercent, InDeltaTime, 3.0f);
    HPSecond->SetPercent(InterpolatedPercent);
}

