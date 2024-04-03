// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelActors/Sky.h"

// Sets default values
ASky::ASky()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASky::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASky::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

