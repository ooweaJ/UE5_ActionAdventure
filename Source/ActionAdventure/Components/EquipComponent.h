#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/Weapon/Weapon.h"
#include "EquipComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONADVENTURE_API UEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE AWeapon* GetCurrentWeapon() { return CurrentWeapon; }
	
	void WeaponL();
	void SelectWeapon(int32 WeaponNum);
	void AddWeapons(TSubclassOf<AWeapon> EquipWeapon);
	void EndDead();
private:
	UPROPERTY(EditAnywhere)
	TArray<AWeapon*> EquipWeapons;
	AWeapon* CurrentWeapon;
	AWeapon* DefaultWeapon;

	class UStateComponent* State;

	class ACharacter* OwnerCharacter;
};