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
	GameTime = 13.0f;
    DAN = EDayAndNight::Dusk;
}

void ACWeatherEvent::BeginPlay()
{
	Super::BeginPlay();

    {
        TArray<AActor*> FoundActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), FoundActors);
        if (FoundActors.Num() > 0)
        {
            DirectionalLight = Cast<ADirectionalLight>(FoundActors[0]);
            SunComp = DirectionalLight->GetComponent();
            DirectionalLight->SetActorRotation(FRotator(0, 314, 0));
        }
    }


    {
        TArray<AActor*> FoundActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AExponentialHeightFog::StaticClass(), FoundActors);
        if (FoundActors.Num() > 0)
           Fog = Cast<AExponentialHeightFog>(FoundActors[0]);
    }

    {
        TArray<AActor*> FoundActors2;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACSky::StaticClass(), FoundActors2);
        if (FoundActors2.Num() > 0)
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

    // 낮과 밤 상태 변경
    // 밤
    if (GameTime <= 6.f || GameTime >= 23.f)
    {
        if (DAN != EDayAndNight::Night)
        {
            SunComp->SetIntensity(0.5f);
            SunComp->SetLightColor(FLinearColor(0.26f, 0.27f, 0.54f));
            DirectionalLight->SetActorRotation(FRotator(146.f, 0.f,  0.f));
            if (!!SKY)
                SKY->SetNightSky();
            DAN = EDayAndNight::Night;
        }
    }
    // 노을
    else if (GameTime >= 6.f && GameTime <= 12.f)
    {
        if (DAN != EDayAndNight::Dusk)
        {
            DirectionalLight->SetActorRotation(FRotator(180.f,0.f, 0.f));
            SunComp->SetLightColor(FLinearColor(1, 1, 1));
            if (!!SKY)
                SKY->SetDefaultSky();
            DAN = EDayAndNight::Dusk;
        }
        FRotator rotator(DeltaTime, 0, 0);
        DirectionalLight->AddActorLocalRotation(rotator);

    }
    // 낮
    else if (GameTime >= 12.f && GameTime <= 18.f)
    {
        if (DAN != EDayAndNight::Day)
        {
            SunComp->SetIntensity(0.7f);
            SunComp->SetLightColor(FLinearColor(1, 1, 1));
            DirectionalLight->SetActorRotation(FRotator(314.f ,0.f, 0.f));

            if (!!SKY)
                SKY->SetDefaultSky();
            DAN = EDayAndNight::Day;
        }
    }
    // 노을
    else if (GameTime >= 18.f && GameTime <= 23.f)
    {
        if (DAN != EDayAndNight::Dusk)
        {
            DirectionalLight->SetActorRotation(FRotator(347.f, 0.f,  0.f));
            DAN = EDayAndNight::Dusk;
        }
        FRotator rotator(DeltaTime, 0, 0);
        DirectionalLight->AddActorLocalRotation(rotator);
    }
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
    UExponentialHeightFogComponent* fogcomp = Fog->GetComponent();
    fogcomp->SetFogDensity(1.0f);
    fogcomp->SetFogInscatteringColor(FLinearColor(1, 1, 1));
}

