// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "DissolveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONADVENTURE_API UDissolveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDissolveComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Play();
	void Stop();

private:
	UFUNCTION()
	void OnStartTimeline(float Output);
private:
	UPROPERTY(EditDefaultsOnly)
	class UMaterialInstanceConstant* Material;

	UPROPERTY(EditDefaultsOnly)
	class UCurveFloat* Curve;

	UPROPERTY(EditDefaultsOnly)
	float PlayRate = 0.2f;
private:
	UPROPERTY()
	class UMaterialInstanceDynamic* DynamicMaterial;

	FTimeline Timeline;
};
