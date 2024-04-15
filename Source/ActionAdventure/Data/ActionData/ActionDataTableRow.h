// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ActionDataTableRow.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
	FName StartSection;

	UPROPERTY(EditAnywhere)
	bool bCanMove = true;

	UPROPERTY(EditAnywhere)
	bool bPawnControl = true;
};

USTRUCT(BlueprintType)
struct FActionData : public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Power;

	UPROPERTY(EditAnywhere)
	float HitStop;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* Effect;

	UPROPERTY(EditAnywhere)
	FTransform EffectTransform;

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class UCameraShake> ShakeClass;

	UPROPERTY(EditAnywhere)
	FString SpecificCollisionName = "None";
};

USTRUCT(BlueprintType)
struct ACTIONADVENTURE_API FActionDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FActionData> ActionDatas;
};
