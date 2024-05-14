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
	void MoveAttack();
	void RangeAttack();
	void TargetDotAction();
	void StrafeAttack();

	void LoopMotion();
protected:
	FActionDataTableRow* ApproachData;
	FActionDataTableRow* SkillData;
	FActionDataTableRow* ComboData;
	FActionDataTableRow* MoveData;
	FActionDataTableRow* FakeData;
	FActionDataTableRow* Fake2Data;
	FActionData PreData;

	class AAIBoss* Boss;
	class UBossBehaviorComponent* Behavior;

	class UAnimMontage* Fake;
	class UAnimMontage* Fake2;
	class UAnimMontage* PreLoop;

	int32 LoopIndex = 0;
	int32 LoopPower = 0;
	int32 LoopMax = 0;
	int32 FakeIndex = 0;
	bool bCombo;
};