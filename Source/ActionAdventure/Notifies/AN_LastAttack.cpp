#include "Notifies/AN_LastAttack.h"
#include "AN_LastAttack.h"
#include "Characters/AI/AIBoss.h"
#include "Characters/Players/CPlayer.h"

FString UAN_LastAttack::GetNotifyName_Implementation() const
{
	return "LastAttack";
}

void UAN_LastAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr) return;

	AAIBoss* Boss = Cast<AAIBoss>(MeshComp->GetOwner());
	if (Boss == nullptr) return;

	Boss->Player->BossSkillEnd();
}
