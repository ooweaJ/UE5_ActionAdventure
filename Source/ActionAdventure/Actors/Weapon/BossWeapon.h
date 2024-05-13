#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapon/Weapon.h"
#include "BossWeapon.generated.h"

UCLASS()
class ACTIONADVENTURE_API ABossWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	ABossWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void MouseL();
	virtual void MouseR();

	virtual void OffMouseR();

	virtual void BeginAction();
	virtual void EndAction();

	void Approach();
	void FakeAttack();

	void RangeAttack();
protected:
	FActionDataTableRow* ApproachData;
	TArray<FActionData> ComboData;
	bool bCombo;
	class AAIBoss* Boss;
	class UBossBehaviorComponent* Behavior;
};
