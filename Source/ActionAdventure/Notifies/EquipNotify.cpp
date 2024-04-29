// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/EquipNotify.h"
#include "Components/EquipComponent.h"
#include "Actors/Weapon/Weapon.h"
#include "Actors/Weapon/Attachment.h"

FString UEquipNotify::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UEquipNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;
	Equip->GetCurrentItem()->GetAttachment()->OnEquip();
}
