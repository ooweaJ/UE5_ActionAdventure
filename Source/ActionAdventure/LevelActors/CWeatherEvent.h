#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeatherEvent.generated.h"

UENUM(BlueprintType)
enum class EWeather : uint8
{
	Sun,
	Rain,
	Snow,
	Fog,
	Max
};

UENUM(BlueprintType)
enum class EDayAndNight : uint8
{
	Day,
	Dusk,
	Night
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDayNightChangedDelegate, EDayAndNight, NewDayNight);

UCLASS()
class ACTIONADVENTURE_API ACWeatherEvent : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWeatherEvent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintAssignable,BlueprintReadWrite)
	FDayNightChangedDelegate OnDayNightChanged;
	UFUNCTION(BlueprintCallable)
	EDayAndNight GetDayAndNight() const { return DAN; }

	EWeather GetWeather();

public:
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void SetMoring();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void SetNight();
private:
	void SetWeatherEvent();
	void SetDefaultWeather();

	void SetSunWeather();
	void SetRainWeather();
	void SetSnowWeather();
	void SetFogWeather();
public:
	UPROPERTY(EditAnywhere)
	float DayTime = 2.f;

	float GameTime;

	UPROPERTY()
	class ADirectionalLight* DirectionalLight;
	class AExponentialHeightFog* Fog;
	class UDirectionalLightComponent* SunComp;
	class ASkyAtmosphere* Skysphere;
	UPROPERTY()
	class AExponentialHeightFog* ExponentialHeightFog;

	class ASky* SKY;

	EDayAndNight DAN;
	bool bSwitchDAN = false;
	bool bWeather = false;
};
