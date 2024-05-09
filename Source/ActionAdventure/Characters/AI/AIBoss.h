#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIBoss.generated.h"

UCLASS()
class ACTIONADVENTURE_API AAIBoss : public ACharacter
{
	GENERATED_BODY()

public:
	AAIBoss();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetMoveDirection(const FVector Direction);

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

	UPROPERTY(VisibleDefaultsOnly)

	class UPaperSpriteComponent* PaperComponent;

	UPROPERTY(VisibleDefaultsOnly)
	class UMontagesComponent* MontagesComponent;

private:
	FVector MovingDirection;
};
