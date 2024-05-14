#include "Notifies/ComboNotifyState.h"
#include "Components/EquipComponent.h"
#include "Actors/Weapon/Melee/MeleeWeapon.h"
#include "Actors/Weapon/Attachment.h"

FString UComboNotifyState::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UComboNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration,EventReference);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;
	Cast<AMeleeWeapon>(Equip->GetCurrentItem())->OnCanCombo();
}

void UComboNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation,EventReference);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;	
	Cast<AMeleeWeapon>(Equip->GetCurrentItem())->OffCanCombo();
}
