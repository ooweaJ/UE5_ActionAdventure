#include "Notifies/ComboNotifyState.h"
#include "Components/EquipComponent.h"
#include "Actors/Weapon/Melee/MeleeWeapon.h"
#include "Actors/Weapon/Attachment.h"

FString UComboNotifyState::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UComboNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;
	Cast<AMeleeWeapon>(Equip->GetCurrentWeapon())->OnCanCombo();
}

void UComboNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;	
	Cast<AMeleeWeapon>(Equip->GetCurrentWeapon())->OffCanCombo();
}
