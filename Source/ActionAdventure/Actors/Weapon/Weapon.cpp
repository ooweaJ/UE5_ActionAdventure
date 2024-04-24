#include "Actors/Weapon/Weapon.h"
#include "GameFramework/Character.h"

#include "Actors/Weapon/Attachment.h"
#include "Components/ActionComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"

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
	OwnerCharacter = InOnwerCharacter;
	WeaponType = InData->ActionType;
	{
		FTransform DefaultTransform;
		AAttachment* Actor = InOnwerCharacter->GetWorld()->SpawnActorDeferred<AAttachment>(InData->Attachment, DefaultTransform, InOnwerCharacter, InOnwerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Actor->FinishSpawning(DefaultTransform, true);
		Attachment = Actor;
		Attachment->AttachToComponent(InOnwerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InData->SocketName);
	}

	DefaultData = WeaponData->Data.GetRow<FActionDataTableRow>(TEXT(""));

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	State = Cast<UStateComponent>(OwnerCharacter->GetComponentByClass<UStateComponent>());
	Status = Cast<UStatusComponent>(OwnerCharacter->GetComponentByClass<UStatusComponent>());
	Attachment->OnAttachmentBeginOverlap.AddDynamic(this, &ThisClass::OnAttachmentBeginOverlap);
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::Attack()
{

}

void AWeapon::EquipWeapon()
{
	if (!State->IsIdleMode()) return;
	State->SetEquipMode();
	OwnerCharacter->PlayAnimMontage(WeaponData->Equip.AnimMontage);
}

void AWeapon::UnEquipWeapon()
{
	if (!State->IsIdleMode()) return;
	Attachment->OnUnequip();
}

void AWeapon::BeginAction()
{
}

void AWeapon::EndAction()
{
	State->SetIdleMode();
	Status->SetMove();
}
