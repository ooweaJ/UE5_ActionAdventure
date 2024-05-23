#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StateComponent.h"
#include "Engine/DataTable.h"
#include "MontagesComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EStateType Type;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
	FName StartSection;

	UPROPERTY(EditAnywhere)
	bool bCanMove;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONADVENTURE_API UMontagesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMontagesComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float PlayKnockBack();
	float PlayGetting();
	float PlayVault();
	void PlayBossAvoid();
	void PlayRoll();

private:
	float PlayAnimMontage(FName Key);

private:
	UDataTable* DataTable;
};
