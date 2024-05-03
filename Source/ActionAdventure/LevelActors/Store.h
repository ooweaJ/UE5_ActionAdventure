#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Store.generated.h"

UCLASS()
class ACTIONADVENTURE_API AStore : public AActor
{
	GENERATED_BODY()
	
public:	
	AStore();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* TextRender;

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Scene;
};
