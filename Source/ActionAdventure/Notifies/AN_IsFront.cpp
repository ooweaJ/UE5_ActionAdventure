#include "Notifies/AN_IsFront.h"
#include "Components/EquipComponent.h"
#include "Actors/Weapon/Weapon.h"
#include "Actors/Weapon/BossWeapon.h"

FString UAN_IsFront::GetNotifyName_Implementation() const
{
	return "SlowAction";
}

void UAN_IsFront::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;

	ABossWeapon* Weapon = Cast<ABossWeapon>(Equip->GetCurrentItem());
	if (Weapon == nullptr) return;

	Weapon->SlowAction();
}
