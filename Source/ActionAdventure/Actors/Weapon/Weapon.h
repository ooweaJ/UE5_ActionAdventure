#pragma once

#include "CoreMinimal.h"
#include "Actors/Item.h"
#include "Engine/DamageEvents.h"
#include "Weapon.generated.h"

UCLASS()
class ACTIONADVENTURE_API AWeapon : public AItem
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	FORCEINLINE FString GetSpecificCollisionName() { return PreData.SpecificCollisionName; }
protected:
	virtual void BeginPlay() override;
	void MontageData(const FActionData& InData);
public:	
	virtual void Tick(float DeltaTime) override;

	void ClearHittedCharacters();

protected:
	FActionData PreData;
	TArray<class ACharacter*> HittedCharacters;

};
