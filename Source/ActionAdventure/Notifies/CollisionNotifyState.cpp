// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/CollisionNotifyState.h"
#include "Components/EquipComponent.h"
#include "Actors/Weapon/Melee/MeleeWeapon.h"
#include "Actors/Weapon/Attachment.h"

FString UCollisionNotifyState::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCollisionNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation,TotalDuration);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;
	AMeleeWeapon* MeleeWeapon = Cast<AMeleeWeapon>(Equip->GetCurrentWeapon());
	if (!!MeleeWeapon)
	{
		FString collisionName = MeleeWeapon->GetSpecificCollisionName();
		Equip->GetCurrentWeapon()->GetAttachment()->OnCollisions(collisionName);
	}
	else
		Equip->GetCurrentWeapon()->GetAttachment()->OnCollisions("");
}

void UCollisionNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;
	Equip->GetCurrentWeapon()->GetAttachment()->OffCollisions();
}
