#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class ACTIONADVENTURE_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAICharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Dead();

	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;
		
public:
	UPROPERTY(VisibleDefaultsOnly)
	class UStatusComponent* StatusComponent;

	UPROPERTY(VisibleDefaultsOnly)
	class UStateComponent* StateComponent;

	UPROPERTY(VisibleDefaultsOnly)
	class UMoveComponent* MoveComponent;

	UPROPERTY(VisibleDefaultsOnly)
	class UActionComponent* ActionComponent;

	UPROPERTY(VisibleDefaultsOnly)
	class UEquipComponent* EquipComponent;

public:
	TArray<USkeletalMesh*> Meshs;

	class ACharacter* Attacker;

	float Damage;
};
