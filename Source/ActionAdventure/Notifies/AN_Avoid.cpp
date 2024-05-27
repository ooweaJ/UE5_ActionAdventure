#include "Notifies/AN_Avoid.h"
#include "Characters/AI/AIBoss.h"

FString UAN_Avoid::GetNotifyName_Implementation() const
{
	return "Avoid";
}

void UAN_Avoid::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr) return;

	AAIBoss* Boss = Cast<AAIBoss>(MeshComp->GetOwner());
	if (Boss == nullptr) return;

	Boss->AvoidTarget();
}
