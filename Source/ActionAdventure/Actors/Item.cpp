#include "Actors/Item.h"
#include "Actors/Weapon/Attachment.h"
#include "Components/ActionComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"

#include "GameFramework/Character.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(Scene);
}

void AItem::SetItemData(ACharacter* InOnwerCharacter, const FItemActionData* InData)
{
	if (!InData) return;
	ActionData = InData;
	OwnerCharacter = InOnwerCharacter;
	ItemType = InData->ActionType;
	{
		FTransform DefaultTransform;
		AAttachment* Actor = InOnwerCharacter->GetWorld()->SpawnActorDeferred<AAttachment>(InData->Attachment, DefaultTransform, InOnwerCharacter, InOnwerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Actor->FinishSpawning(DefaultTransform, true);
		Attachment = Actor;
		Attachment->AttachToComponent(InOnwerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InData->SocketName);
	}

	DefaultData = ActionData->Data.GetRow<FActionDataTableRow>(TEXT(""));
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	State = Cast<UStateComponent>(OwnerCharacter->GetComponentByClass<UStateComponent>());
	Status = Cast<UStatusComponent>(OwnerCharacter->GetComponentByClass<UStatusComponent>());
	Action = Cast<UActionComponent>(OwnerCharacter->GetComponentByClass<UActionComponent>());
	Attachment->OnAttachmentBeginOverlap.AddDynamic(this, &ThisClass::OnAttachmentBeginOverlap);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::MouseL()
{
}

void AItem::EquipItem()
{
	if (!State->IsIdleMode()) return;
	State->SetEquipMode();
	OwnerCharacter->PlayAnimMontage(ActionData->Equip.AnimMontage);
}

void AItem::UnEquipItem()
{
	if (!State->IsIdleMode()) return;
	Attachment->OnUnequip();
}

void AItem::MouseR()
{
}

void AItem::OffMouseR()
{
}

void AItem::BeginAction()
{
}

void AItem::EndAction()
{
	State->SetIdleMode();
	Status->SetMove();
}

