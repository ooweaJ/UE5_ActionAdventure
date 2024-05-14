#include "Notifies/ANS_Fly.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

FString UANS_Fly::GetNotifyName_Implementation() const
{
	return "Fly";
}

void UANS_Fly::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (MeshComp == nullptr) return;

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character == nullptr) return;

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UANS_Fly::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp == nullptr) return;

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character == nullptr) return;

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}
