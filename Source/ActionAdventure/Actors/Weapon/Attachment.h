// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Attachment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap, class ACharacter*, InAttacker, class AActor*, InCauser, class ACharacter*, InOtherCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentEndOverlap, class ACharacter*, InAttacker, class AActor*, InCauser, class ACharacter*, InOtherCharacter);


UCLASS()
class ACTIONADVENTURE_API AAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	AAttachment();
	void SetOwnerCharacter(ACharacter* InOwnerCharacter);
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent)
	void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
	void OnUnequip();

	void OnCollisions(FString InCollisionName = "None");
	void OffCollisions();

	UFUNCTION(BlueprintCallable)
	void AttachToCollision(class USceneComponent* InComponent, FName InSocketName);
private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(BlueprintAssignable)
	FAttachmentBeginOverlap OnAttachmentBeginOverlap;

	UPROPERTY(BlueprintAssignable)
	FAttachmentEndOverlap OnAttachmentEndOverlap;
private:
	TArray<class UShapeComponent*> ShapeComponents;
	USceneComponent* Scene;
	class ACharacter* OwnerCharacter;
};
