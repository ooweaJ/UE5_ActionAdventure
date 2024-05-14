// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/CollisionNotifyState.h"
#include "Components/EquipComponent.h"
#include "Actors/Weapon/Melee/MeleeWeapon.h"
#include "Actors/Weapon/Attachment.h"

FString UCollisionNotifyState::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCollisionNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation,TotalDuration, EventReference);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;
	AMeleeWeapon* MeleeWeapon = Cast<AMeleeWeapon>(Equip->GetCurrentItem());
	if (!!MeleeWeapon)
	{
		FString collisionName = MeleeWeapon->GetSpecificCollisionName();
		Equip->GetCurrentItem()->GetAttachment()->OnCollisions(collisionName);
	}
	else
		Equip->GetCurrentItem()->GetAttachment()->OnCollisions("");
}

void UCollisionNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;
	Equip->GetCurrentItem()->GetAttachment()->OffCollisions();
}
