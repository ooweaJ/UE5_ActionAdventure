#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sidewalk.generated.h"

UCLASS()
class ACTIONADVENTURE_API ASidewalk : public AActor
{
	GENERATED_BODY()
	
public:	
	ASidewalk();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FVector SetNextWalkPoint();
	
	void GetWalkPoint();

public:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	UPROPERTY(EditAnywhere, Category = "Point")
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere, Category = "Point")
	class UTextRenderComponent* TextRender;

	UPROPERTY(EditAnywhere, Category = "Point")
	ASidewalk* NorthPoint;

	UPROPERTY(EditAnywhere, Category = "Point")
	ASidewalk* SouthPoint;

	UPROPERTY(EditAnywhere, Category = "Point")
	ASidewalk* EastPoint;

	UPROPERTY(EditAnywhere, Category = "Point")
	ASidewalk* WestPoint;

private:
	TArray<FVector> Point;

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Scene;
};
