#include "LevelActors/CWeatherEvent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DirectionalLight.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"

#include "LevelActors/Sky.h"

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
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASky::StaticClass(), FoundActors2);
        if (FoundActors2.Num() > 0)
            SKY = Cast<ASky>(FoundActors2[0]);
    }

    {
        ASkyAtmosphere* actor = Cast<ASkyAtmosphere>(UGameplayStatics::GetActorOfClass(GetWorld(), ASkyAtmosphere::StaticClass()));
        if (!!actor)
            Skysphere = actor;
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
        if (!bWeather)
        {
            bWeather = true;
        }
    }

    float Pitch = 0.0f;
    // 낮과 밤 상태 변경
    // 밤
    if (GameTime <= 6.f || GameTime >= 23.f)
    {
        
        Pitch = 134.f;
        if (DAN != EDayAndNight::Night)
        {
            //SunComp->SetIntensity(0.5f);
            SunComp->SetLightColor(FLinearColor(0.26f, 0.27f, 0.54f));
            DAN = EDayAndNight::Night;
            SetWeatherEvent();

        }
    }
    // 노을
    else if (GameTime >= 6.f && GameTime <= 12.f)
    {
        Pitch = FMath::Lerp(2.0f, -5.0f, (GameTime - 6.f) / 6.f);
        if (DAN != EDayAndNight::Dusk)
        {
            SunComp->SetLightColor(FLinearColor(1, 1, 1));
            DAN = EDayAndNight::Dusk;
        }
    }
    // 낮
    else if (GameTime >= 12.f && GameTime <= 18.f)
    {
        Pitch = FMath::Lerp(-5.0f, -46.0f, (GameTime - 12.f) / 6.f);
        if (DAN != EDayAndNight::Day)
        {
            //SunComp->SetIntensity(10.0f);
            SunComp->SetLightColor(FLinearColor(1, 1, 1));
            DAN = EDayAndNight::Day;
        }
    }
    // 노을
    else if (GameTime >= 18.f && GameTime <= 23.f)
    {
        Pitch = FMath::Lerp(-5.0f, 5.0f, (GameTime - 18.f) / 5.f);
        if (DAN != EDayAndNight::Dusk)
        {
            DAN = EDayAndNight::Dusk;
        }
    }
    FRotator Rotator = FRotator(Pitch, 0, 0);
    DirectionalLight->SetActorRotation(Rotator);
}

EWeather ACWeatherEvent::GetWeather()
{
    EWeather RandomWeather = static_cast<EWeather>(UKismetMathLibrary::RandomIntegerInRange(0, static_cast<int32>(EWeather::Max) - 1));

    return RandomWeather;
}

void ACWeatherEvent::SetWeatherEvent()
{
    bWeather = false;
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

void ACWeatherEvent::SetDefaultWeather()
{
    SunComp->SetLightColor(FLinearColor(1, 1, 1));
    SunComp->SetIntensity(10.f);
    Skysphere->GetComponent()->SetRayleighScattering(FLinearColor(0.17, 0.409, 1.0));
    UExponentialHeightFogComponent* fogcomp = Fog->GetComponent();
    FExponentialHeightFogData fogdata;
    fogcomp->SetSecondFogData(fogdata);
    fogcomp->SetFogInscatteringColor(FLinearColor(0, 0, 0));
    fogcomp->SetFogDensity(0.02f);
}

void ACWeatherEvent::SetSunWeather()
{
    SetDefaultWeather();
    if (!!SKY)
        SKY->SetDefaultSky();
}

void ACWeatherEvent::SetRainWeather()
{
    SunComp->SetIntensity(5.f);
    Skysphere->GetComponent()->SetRayleighScattering(FLinearColor(0.23, 0.23, 0.23));
    UExponentialHeightFogComponent* fogcomp = Fog->GetComponent();
    FExponentialHeightFogData fogdata;
    fogdata.FogDensity = 0.01f;
    fogcomp->SetSecondFogData(fogdata);
    fogcomp->SetFogDensity(0.02f);
    fogcomp->SetFogInscatteringColor(FLinearColor(0, 0, 0));
    if (!!SKY)
        SKY->SetRainSky();
}

void ACWeatherEvent::SetSnowWeather()
{
    SunComp->SetIntensity(5.f);
    Skysphere->GetComponent()->SetRayleighScattering(FLinearColor(0.5, 0.95, 1));
    UExponentialHeightFogComponent* fogcomp = Fog->GetComponent();
    FExponentialHeightFogData fogdata;
    fogcomp->SetSecondFogData(fogdata);
    fogcomp->SetFogDensity(0.02f);
    fogcomp->SetFogInscatteringColor(FLinearColor(0, 0, 0));
    if (!!SKY)
        SKY->SetSnowSky();
}

void ACWeatherEvent::SetFogWeather()
{
    if (SKY)
        SKY->SetFogSky();
    SunComp->SetIntensity(5.f);
    Skysphere->GetComponent()->SetRayleighScattering(FLinearColor(0.23, 0.23, 0.23));
    UExponentialHeightFogComponent* fogcomp = Fog->GetComponent();
    fogcomp->SetFogDensity(0.5f);
    fogcomp->SetFogInscatteringColor(FLinearColor(1, 1, 1));
}

