#include "Notifies/EndActionNotify.h"
#include "Components/EquipComponent.h"
#include "Actors/Weapon/Weapon.h"

FString UEndActionNotify::GetNotifyName_Implementation() const
{
	return "EndAction";
}

void UEndActionNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;

	Equip->GetCurrentItem()->EndAction();
}