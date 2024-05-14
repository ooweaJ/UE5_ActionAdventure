#include "Notifies/AN_Loop.h"
#include "Components/EquipComponent.h"
#include "Actors/Weapon/BossWeapon.h"

FString UAN_Loop::GetNotifyName_Implementation() const
{
	return "Loop";
}

void UAN_Loop::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;

	ABossWeapon* Bossweapon = Cast<ABossWeapon>(Equip->GetCurrentItem());
	if (Bossweapon == nullptr) return;

	Bossweapon->LoopMotion();
}
