// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/ActionData/ActionDataTableRow.h"
#include "Components/ActionComponent.h"
#include "Weapon.generated.h"

USTRUCT()
struct ACTIONADVENTURE_API FWeaponData : public FTableRowBase
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, meta=(RowType = "/Script/ACTIONADVENTURE.ActionDataTableRow"))
	FDataTableRowHandle Data;

	UPROPERTY(EditAnywhere, category = "Attach")
	TSubclassOf<class AAttachment> Attachment;

	UPROPERTY(EditAnywhere, category = "Attach")
	FName SocketName;

	UPROPERTY(EditAnywhere)
	EActionType ActionType;
};

UCLASS()
class ACTIONADVENTURE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	void SetWeaponData(class ACharacter* InOnwerCharacter, const FWeaponData* InData);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Attack();
	virtual void EquipWeapon();
	virtual void UnEquipWeapon();

	const FWeaponData* WeaponData;

	USceneComponent* Scene;
	class AAttachment* Attachment;

	FName KeyValue;

private:
	UPROPERTY(EditAnywhere)
	EActionType WeaponType;
};
