#include "Actors/Weapon/Weapon.h"
#include "GameFramework/Character.h"
#include "Components/StatusComponent.h"

AWeapon::AWeapon()
{

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AWeapon::MontageData(const FActionData& InData)
{
	InData.bCanMove ? Status->SetMove() : Status->SetStop();
	PreData = InData;
	OwnerCharacter->PlayAnimMontage(InData.AnimMontage, InData.PlayRate, InData.StartSection);
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
