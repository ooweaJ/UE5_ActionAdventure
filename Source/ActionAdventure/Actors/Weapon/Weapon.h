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

	virtual void BeginAction();
	virtual void EndAction();
public:
	UFUNCTION()
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {};

	UFUNCTION()
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {};

	FORCEINLINE class AAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE EActionType GetActiontype() { return WeaponType; }

public:
	const FWeaponData* WeaponData;
	class AAttachment* Attachment;
	USceneComponent* Scene;
	FName KeyValue;

	class ACharacter* OwnerCharacter;
	class UStateComponent* State;
	class UStatusComponent* Status;

	struct FActionDataTableRow* DefaultData;
private:
	UPROPERTY(EditAnywhere)
	EActionType WeaponType;
};
