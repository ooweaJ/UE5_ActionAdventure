#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, Assassin, Kanata, Rifle, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONADVENTURE_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	FORCEINLINE bool IsAiming() { return bAiming; }
public:
	void MouseL();
	void MouseR();
	void OffMouseR();
	void Num1();
	void Num2();
	void Num3();

	void SetActionMode(EActionType InNewType);
	void SetUnarmed();
	void SetAssassin();
	void SetKanata();

	void OnAim() { bAiming = true; }
	void OffAim() { bAiming = false; }

	void EndDead();
public:
	UPROPERTY(BlueprintAssignable)
	FActionTypeChanged OnActionTypeChanged;

private:
	EActionType Type;

	class ACharacter* OwnerCharacter;

	bool bAiming = false;
};
