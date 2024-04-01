// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sky.generated.h"

UCLASS()
class ACTIONADVENTURE_API ASky : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASky();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetDefaultSky();

	UFUNCTION(BlueprintImplementableEvent)
	void SetFogSky();

	UFUNCTION(BlueprintImplementableEvent)
	void SetSnowSky();

	UFUNCTION(BlueprintImplementableEvent)
	void SetRainSky();
};
