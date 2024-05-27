#include "Notifies/AN_RandomAttack.h"
#include "Components/EquipComponent.h"
#include "Actors/Weapon/BossWeapon.h"

FString UAN_RandomAttack::GetNotifyName_Implementation() const
{
	return "Random";
}

void UAN_RandomAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;

	ABossWeapon* Bossweapon = Cast<ABossWeapon>(Equip->GetCurrentItem());
	if (Bossweapon == nullptr) return;

	Bossweapon->MouseR();
}
