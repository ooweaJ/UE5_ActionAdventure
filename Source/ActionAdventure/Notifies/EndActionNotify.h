#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndActionNotify.generated.h"

UCLASS()
class ACTIONADVENTURE_API UEndActionNotify : public UAnimNotify
{
	GENERATED_BODY()
	
	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
