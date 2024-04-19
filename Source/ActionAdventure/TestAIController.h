// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TestAIController.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONADVENTURE_API ATestAIController : public AAIController
{
	GENERATED_BODY()
public:
	ATestAIController();
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
