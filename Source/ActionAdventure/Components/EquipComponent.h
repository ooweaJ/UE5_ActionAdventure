#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/Item.h"
#include "EquipComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONADVENTURE_API UEquipComponent : public UActorComponent
{
	GENERATED_BODY()
	friend class UEquipWindowWidget;
public:	
	UEquipComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE AItem* GetCurrentItem() { return CurrentItem; }
	
	void WeaponL();
	void WeaponR();
	void OffWeaponR();

	void SelectWeapon(int32 WeaponNum);

	bool AddItem(FItemData* ItemData);
	void AddData(FItemData* InData);

	void EquipItem(TSubclassOf<AItem> EquipItem);
	void UnEquipItem(int32 index);

	void EndDead();
	
private:
	bool CanIsPool();

private:
	UPROPERTY(EditAnywhere)
	TArray<AItem*> EquipItems;
	TArray<FItemData*> ItemDatas;


	AItem* CurrentItem;
	AItem* DefaultWeapon;

	class UStateComponent* State;

	class ACharacter* OwnerCharacter;
};