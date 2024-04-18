#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapon/Weapon.h"
#include "MeleeWeapon.generated.h"

UCLASS()
class ACTIONADVENTURE_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;

	virtual void Attack() override;
	virtual void BeginAction() override;
	virtual void EndAction() override;
	FORCEINLINE void OnCanCombo() { bCanCombo = true; }
	FORCEINLINE void OffCanCombo() { bCanCombo = false; }
	FORCEINLINE FString GetSpecificCollisionName() { return DefaultData->ActionDatas[ComboCount].SpecificCollisionName; }

	UFUNCTION()
	void RestoreGlobalTimeDilation();
private:
	int32 ComboCount;
	bool bCanCombo;
	bool bSucceed;
};
