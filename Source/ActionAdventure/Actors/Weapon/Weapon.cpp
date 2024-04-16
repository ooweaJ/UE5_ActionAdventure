// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/Weapon.h"
#include "GameFramework/Character.h"

#include "Actors/Weapon/Attachment.h"
#include "Components/ActionComponent.h"


// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(Scene);
}

void AWeapon::SetWeaponData(class ACharacter* InOnwerCharacter, const FWeaponData* InData)
{
	if (!InData) return;
	WeaponData = InData;
	WeaponType = InData->ActionType;
	{
		FTransform DefaultTransform;
		AAttachment* Actor = InOnwerCharacter->GetWorld()->SpawnActorDeferred<AAttachment>(InData->Attachment, DefaultTransform, InOnwerCharacter, InOnwerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Actor->FinishSpawning(DefaultTransform, true);
		Attachment = Actor;
		Attachment->AttachToComponent(InOnwerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InData->SocketName);
	}

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::Attack()
{
	FActionDataTableRow* data = WeaponData->Data.GetRow<FActionDataTableRow>(TEXT(""));
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	int32 Randomint = FMath::RandRange(0, data->ActionDatas.Num() - 1);
	OwnerCharacter->PlayAnimMontage(data->ActionDatas[Randomint].AnimMontage);
}

void AWeapon::EquipWeapon()
{
	Attachment->OnEquip();
}

void AWeapon::UnEquipWeapon()
{
	Attachment->OnUnequip();
}

