#include "LevelActors/Sidewalk.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Characters/AI/AICharacter.h"
#include "Characters/Controller/CAIController.h"

ASidewalk::ASidewalk()
{
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(Scene);

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	TextRender = CreateDefaultSubobject<UTextRenderComponent>("Text");

	Box->SetupAttachment(Scene);
	TextRender->SetupAttachment(Scene);

	Box->SetBoxExtent(FVector(500, 500, 300));
	Box->SetRelativeLocation(FVector(0, 0, 290));

	TextRender->TextRenderColor = FColor::Red;
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextRender->WorldSize = 100.f;
}

void ASidewalk::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
	GetWalkPoint();
}

void ASidewalk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Box->UpdateOverlaps();
}

FVector ASidewalk::SetNextWalkPoint()
{
	int32 randomint = FMath::RandRange(0, Point.Num() - 1);
	return Point[randomint];
}

void ASidewalk::GetWalkPoint()
{
	if(!!NorthPoint)
		Point.Add(NorthPoint->GetActorLocation());

	if (!!SouthPoint)
		Point.Add(SouthPoint->GetActorLocation());

	if (!!EastPoint)
		Point.Add(EastPoint->GetActorLocation());

	if (!!WestPoint)
		Point.Add(WestPoint->GetActorLocation());
}

void ASidewalk::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAICharacter* aiCharacter = Cast<AAICharacter>(OtherActor);
	if (!aiCharacter) return;

	ACAIController* aicontoller = Cast<ACAIController>(aiCharacter->GetController());
	if (!!aicontoller)
	{
		aicontoller->SetLoactionKey(SetNextWalkPoint());
	}
}

