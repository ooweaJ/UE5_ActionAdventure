#include "BeginActionNotify.h"
#include "Components/EquipComponent.h"
#include "Actors/Weapon/Weapon.h"

FString UBeginActionNotify::GetNotifyName_Implementation() const
{
	return "Begin";
}

void UBeginActionNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;

	Equip->GetCurrentItem()->BeginAction();
}
