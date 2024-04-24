// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGame_Player.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONADVENTURE_API USaveGame_Player : public USaveGame
{
	GENERATED_BODY()
	
public:
	FVector PlayerLocation;
};
