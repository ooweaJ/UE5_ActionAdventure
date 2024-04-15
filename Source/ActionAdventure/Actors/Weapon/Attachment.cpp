// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/Attachment.h"
#include "Components/ShapeComponent.h"

// Sets default values
AAttachment::AAttachment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAttachment::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UShapeComponent>(ShapeComponents);
}

// Called every frame
void AAttachment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

