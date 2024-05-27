#include "Notifies/AN_Projectile.h"
#include "Components/EquipComponent.h"
#include "Actors/Weapon/BossWeapon.h"

FString UAN_Projectile::GetNotifyName_Implementation() const
{
	return "Projectile";
}

void UAN_Projectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;

	ABossWeapon* Bossweapon = Cast<ABossWeapon>(Equip->GetCurrentItem());
	if (Bossweapon == nullptr) return;

	Bossweapon->StrafeAttack();
}
