#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossRange.generated.h"

UCLASS()
class ACTIONADVENTURE_API ABossRange : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossRange();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnAttack();

public:
	class UNiagaraSystem* Niagara;
};
