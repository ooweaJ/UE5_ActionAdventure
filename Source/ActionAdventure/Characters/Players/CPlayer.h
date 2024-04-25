#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CharacterInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

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
	virtual void GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDriection);
	virtual void Hitted(TSubclassOf<UDamageType> Type) {}
	virtual void Dead() {}
	virtual void End_Dead() {}

private:
	UFUNCTION()
	void OffFlying();

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

	void OnOrient();
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

};
