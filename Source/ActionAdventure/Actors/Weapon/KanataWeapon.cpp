// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/KanataWeapon.h"

AKanataWeapon::AKanataWeapon()
{
	KeyValue = TEXT("Kanata");
}

void AKanataWeapon::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
}

void AKanataWeapon::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
}
