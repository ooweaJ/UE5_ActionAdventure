#include "LevelActors/CWeatherEvent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DirectionalLight.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"

#include "LevelActors/CSky.h"

ACWeatherEvent::ACWeatherEvent()
{
	PrimaryActorTick.bCanEverTick = true;
	GameTime = 9.0f;
}

void ACWeatherEvent::BeginPlay()
{
	Super::BeginPlay();
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), FoundActors);

    TArray<AActor*> FoundActors2;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACSky::StaticClass(), FoundActors2);
    if (FoundActors.Num() > 0)
    {
        DirectionalLight = Cast<ADirectionalLight>(FoundActors[0]);
        DirectionalLight->SetActorRotation(FRotator(0, 314, 0));
    }

    if (FoundActors2.Num() > 0)
    {
        SKY = Cast<ACSky>(FoundActors2[0]);
    }
}

void ACWeatherEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    GameTime += DeltaTime * (1 / DayTime);
    
    // GameTime이 24.0을 초과할 경우 초기화
    if (GameTime >= 24.0f)
    {
        GameTime = 0.0f;
        SetWeatherEvent();
    }

    // 이전 상태 저장
    EDayAndNight PreviousDAN = DAN;


    // 낮과 밤 상태 변경
    if (GameTime <= 6.f || GameTime >= 21.f)
    {
        DAN = EDayAndNight::Night;
    }
    else if (GameTime >= 6.f && GameTime <= 8.f)
    {
        // 노을
       // UpdateDirectionalLightAngle();

        DAN = EDayAndNight::Dusk;
    }
    else if (GameTime >= 8.f && GameTime <= 19.f)
    {
        DAN = EDayAndNight::Day;
    }
    else if (GameTime >= 19.f && GameTime <= 21.f)
    {
        // 노을
       // UpdateDirectionalLightAngle();

        DAN = EDayAndNight::Dusk;
    }

    // 낮 밤 상태가 변경되었을 때만 설정 적용
    if (PreviousDAN != DAN)
    {
        UDirectionalLightComponent* comp = DirectionalLight->GetComponent();

        if (DAN == EDayAndNight::Night)
        {
            comp->SetIntensity(0.5f);
            comp->SetLightColor(FLinearColor(0.26f, 0.27f, 0.54f));
            DirectionalLight->SetActorRotation(FRotator(0.f, -46.f,0.f));
            if(!!SKY)
            SKY->SetNightSky();
        }
        else
        {
            comp->SetIntensity(0.7f);
            comp->SetLightColor(FLinearColor(1, 1, 1));
            DirectionalLight->SetActorRotation(FRotator(0.f, 146.f, 0.f));

            if(!!SKY)
            SKY->SetDefaultSky();
        }
    }
}

void ACWeatherEvent::UpdateDirectionalLightAngle()
{
    FRotator LightRotation;
    float alpha = (GameTime / 24.0f);
    float Angle = FMath::Lerp(0.f, 360.f, alpha);
    LightRotation.Pitch = Angle;
    FQuat rotationQuat = LightRotation.Quaternion();
    DirectionalLight->SetActorRotation(rotationQuat);
}

EWeather ACWeatherEvent::GetWeather()
{
    EWeather RandomWeather = static_cast<EWeather>(UKismetMathLibrary::RandomIntegerInRange(0, static_cast<int32>(EWeather::Max) - 1));

    return RandomWeather;
}

void ACWeatherEvent::SetWeatherEvent()
{
    switch (GetWeather())
    {
    case EWeather::Sun:
        SetSunWeather();
        break;
    case EWeather::Rain:
        SetRainWeather();
        break;
    case EWeather::Snow:
        SetSnowWeather();
        break;
    case EWeather::Fog:
        SetFogWeather();
        break;
    }

}

void ACWeatherEvent::SetSunWeather()
{

}

void ACWeatherEvent::SetRainWeather()
{
}

void ACWeatherEvent::SetSnowWeather()
{
}

void ACWeatherEvent::SetFogWeather()
{
}

