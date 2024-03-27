#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeatherEvent.generated.h"

UENUM(BlueprintType)
enum class FWeather : uint8
{
	Sun,
	Rain,
	Snow,
	Fog,
	Max
};

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
	FWeather GetWeather();

private:
	void UpdateDirectionalLightAngle();
	void SetWeatherEvent();

	void SetSunWeather();
	void SetRainWeather();
	void SetSnowWeather();
	void SetFogWeather();
public:
	UPROPERTY()
	float GameTime;

	UPROPERTY(EditAnywhere)
	class ADirectionalLight* DirectionalLight;
	UPROPERTY(EditAnywhere)
	class AExponentialHeightFog* ExponentialHeightFog;
};
