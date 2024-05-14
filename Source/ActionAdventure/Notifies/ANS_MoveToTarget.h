// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_MoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONADVENTURE_API UANS_MoveToTarget : public UAnimNotifyState
{
	GENERATED_BODY()
public:
    FString GetNotifyName_Implementation() const override;

    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
    virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
    FVector TargetLocationOffset;
    FVector StartLocation;
    float MoveDuration;
    float ElapsedTime;
};
