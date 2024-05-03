#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/ActionData/ActionDataTableRow.h"
#include "Components/ActionComponent.h"
#include "Item.generated.h"


USTRUCT()
struct ACTIONADVENTURE_API FItemActionData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/ACTIONADVENTURE.ActionDataTableRow"))
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
class ACTIONADVENTURE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	void SetItemData(class ACharacter* InOnwerCharacter, const FItemActionData* InData);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void MouseL();
	virtual void EquipItem();
	virtual void UnEquipItem();
	virtual void MouseR();
	virtual void OffMouseR();

	virtual void BeginAction();
	virtual void EndAction();
public:
	UFUNCTION()
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {};

	UFUNCTION()
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {};

	FORCEINLINE class AAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE EActionType GetActiontype() { return ItemType; }

public:
	class AAttachment* Attachment;
	USceneComponent* Scene;
	FName KeyValue;
	const FItemActionData* ActionData;

	class ACharacter* OwnerCharacter;
	class UStateComponent* State;
	class UStatusComponent* Status;
	class UActionComponent* Action;

	struct FActionDataTableRow* DefaultData;
private:
	UPROPERTY(EditAnywhere)
	EActionType ItemType;
};
