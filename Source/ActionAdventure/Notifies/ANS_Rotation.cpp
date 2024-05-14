#include "Notifies/ANS_Rotation.h"
#include "Characters/AI/AIBoss.h"
FString UANS_Rotation::GetNotifyName_Implementation() const
{
	return "Rotation";
}

void UANS_Rotation::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (MeshComp == nullptr) return;

	AAIBoss* Boss = Cast<AAIBoss>(MeshComp->GetOwner());
	if (Boss == nullptr) return;
	Boss->bTargetRotation = true;
}

void UANS_Rotation::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp == nullptr) return;

	AAIBoss* Boss = Cast<AAIBoss>(MeshComp->GetOwner());
	if (Boss == nullptr) return;
	Boss->bTargetRotation = false;
}

