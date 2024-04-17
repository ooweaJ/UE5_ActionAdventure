// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InPutDataConfig.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class ACTIONADVENTURE_API UInPutDataConfig : public UObject
{
	GENERATED_BODY()
	
	UInPutDataConfig();

public:
	UInputMappingContext* InputMappingContext = nullptr;

	UInputAction* Move = nullptr;
	UInputAction* Look = nullptr;
	UInputAction* Jump = nullptr;
	UInputAction* Shift = nullptr;
	UInputAction* MouseL = nullptr;
	UInputAction* Num1 = nullptr;
	UInputAction* Num2 = nullptr;
};
