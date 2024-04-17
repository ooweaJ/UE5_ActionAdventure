#include "Notifies/SetIdleNotify.h"
#include "Components/StateComponent.h"

FString USetIdleNotify::GetNotifyName_Implementation() const
{
	return "SetIdle";
}

void USetIdleNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == nullptr) return;

	UStateComponent* State = Cast<UStateComponent>(MeshComp->GetOwner()->GetComponentByClass<UStateComponent>());
	if (State == nullptr) return;

	State->SetIdleMode();
}
