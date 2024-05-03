#include "LevelActors/Store.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Characters/Players/CPlayer.h"

AStore::AStore()
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
	TextRender->WorldSize = 200.f;
	TextRender->SetText(FText::FromString(TEXT("상점")));
}

void AStore::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnComponentEndOverlap);
}

void AStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStore::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	if (player)
		player->SetStore();
}

void AStore::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	if (player)
		player->SetDefault();
}

