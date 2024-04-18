#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapon/Melee/MeleeWeapon.h"
#include "KanataWeapon.generated.h"


UCLASS()
class ACTIONADVENTURE_API AKanataWeapon : public AMeleeWeapon
{
	GENERATED_BODY()
public:
	AKanataWeapon();

	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;
};
