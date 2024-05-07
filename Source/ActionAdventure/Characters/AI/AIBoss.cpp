// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/AIBoss.h"

// Sets default values
AAIBoss::AAIBoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

