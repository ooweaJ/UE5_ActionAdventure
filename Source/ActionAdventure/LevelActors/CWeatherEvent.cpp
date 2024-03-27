#include "LevelActors/CWeatherEvent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DirectionalLight.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"

ACWeatherEvent::ACWeatherEvent()
{
	PrimaryActorTick.bCanEverTick = true;
	GameTime = 0.0f;
}

void ACWeatherEvent::BeginPlay()
{
	Super::BeginPlay();
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), FoundActors);

    if (FoundActors.Num() > 0)
    {
        DirectionalLight = Cast<ADirectionalLight>(FoundActors[0]);
        DirectionalLight->SetActorRotation(FRotator(0, 314, 0));
    }
    UDirectionalLightComponent* Night;
    Night->SetIntensity(0.5f);
    Night->SetLightColor(FLinearColor(0.26f, 0.27f, 0.54f));
}

void ACWeatherEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    GameTime += DeltaTime;
    if (GameTime > 24.0f)
    {
        GameTime = 0.0f;
        SetWeatherEvent();
    }

    UpdateDirectionalLightAngle();
}

FWeather ACWeatherEvent::GetWeather()
{
    FWeather RandomWeather = static_cast<FWeather>(UKismetMathLibrary::RandomIntegerInRange(0, static_cast<int32>(FWeather::Max) - 1));

    return RandomWeather;
}

void ACWeatherEvent::UpdateDirectionalLightAngle()
{
    FRotator LightRotation;
    float Angle = (314 + (GameTime / 24.0f) * (674.f - 314.f));
    LightRotation.Pitch = Angle;
    DirectionalLight->SetActorRotation(LightRotation);
}

void ACWeatherEvent::SetWeatherEvent()
{
    switch (GetWeather())
    {
    case FWeather::Sun:
        SetSunWeather();
        break;
    case FWeather::Rain:
        SetRainWeather();
        break;
    case FWeather::Snow:
        SetSnowWeather();
        break;
    case FWeather::Fog:
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

