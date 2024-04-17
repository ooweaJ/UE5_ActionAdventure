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

	UPROPERTY(EditAnywhere)
	FEquipmentData Equip;
};

UCLASS()
class ACTIONADVENTURE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	void SetWeaponData(class ACharacter* InOnwerCharacter, const FWeaponData* InData);
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Attack();
	virtual void EquipWeapon();
	virtual void UnEquipWeapon();
	virtual void EndAction();

	FORCEINLINE class AAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE EActionType GetActiontype() { return WeaponType; }

	const FWeaponData* WeaponData;

	USceneComponent* Scene;
	class AAttachment* Attachment;

	FName KeyValue;

private:
	UPROPERTY(EditAnywhere)
	EActionType WeaponType;

	class ACharacter* OwnerCharacter;
	class UStateComponent* State;
	class UStatusComponent* Status;
};
