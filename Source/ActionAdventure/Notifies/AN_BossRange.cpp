#include "Notifies/AN_BossRange.h"
#include "Characters/AI/AIBoss.h"
#include "Notifies/AN_BossRange.h"

FString UAN_BossRange::GetNotifyName_Implementation() const
{
	return "Range";
}

void UAN_BossRange::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr) return;

	AAIBoss* Boss = Cast<AAIBoss>(MeshComp->GetOwner());
	if (Boss == nullptr) return;

	Boss->RangeAttack();
}
