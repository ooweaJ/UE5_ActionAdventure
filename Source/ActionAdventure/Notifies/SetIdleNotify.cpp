#include "Notifies/SetIdleNotify.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"

FString USetIdleNotify::GetNotifyName_Implementation() const
{
	return "SetIdle";
}

void USetIdleNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == nullptr) return;

	UStateComponent* State = MeshComp->GetOwner()->GetComponentByClass<UStateComponent>();
	if (State == nullptr) return;

	UStatusComponent* Status = MeshComp->GetOwner()->GetComponentByClass<UStatusComponent>();
	if (Status == nullptr) return;

	Status->SetMove();
	State->SetIdleMode();
}
