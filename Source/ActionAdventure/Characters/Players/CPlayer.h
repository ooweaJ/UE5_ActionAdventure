#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CharacterInterface.h"
#include "Components/TimelineComponent.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UENUM(BlueprintType)
enum class EInteraction : uint8
{
	Default, Store , Max
};

UCLASS()
class ACTIONADVENTURE_API ACPlayer : public ACharacter , public ICharacterInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDriection);
	virtual void Hitted(TSubclassOf<UDamageType> Type) {}
	virtual void Dead();

	UFUNCTION()
	virtual void End_Dead();

private:
	UFUNCTION()
	void OffFlying();

	UFUNCTION()
	void Zooming(float Infloat);
public:
	void OnShift();
	void OffShift();
	void OnMouseL();
	void OnMouseR();
	void OffMouseR();
	void OnNum1();
	void OnNum2();
	void OnNum3();
	void Parkour();
	void OnT();

	void OnAim();
	void OffAim();

	bool IsComBat();
public:
	void SetDefault();
	void SetStore();
	void OnRoll();

	UFUNCTION(BlueprintNativeEvent)
	void BossSkill();
	virtual void BossSkill_Implementation();
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void BossSkillEnd();
	virtual void BossSkillEnd_Implementation();

	UFUNCTION(BlueprintCallable)
	void DetachWeapon();
private:
	void FocusTarget();
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

	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* PaperComponent;
	
	UPROPERTY(EditAnywhere)
	class UMontagesComponent* MontagesComponent;

	UPROPERTY(VisibleDefaultsOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	class UCameraComponent* Camera;

public:
	UPROPERTY(BlueprintReadOnly)
	EInteraction Interaction;

private:
	AActor* TargetActor;

	class ACharacter* Attacker;
	class UUI_UserStatus* UserStatus;
	float Damage;
	TSubclassOf<UUserWidget> DeadClass;
	class UCurveFloat* Curve;

	FTimeline Timeline;
	FOnTimelineFloat TimelineFloat;
};
