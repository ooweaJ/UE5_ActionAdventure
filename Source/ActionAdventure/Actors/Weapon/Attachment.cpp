#include "Actors/Weapon/Attachment.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Character.h"

AAttachment::AAttachment()
{
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
}

void AAttachment::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	GetComponents<UShapeComponent>(ShapeComponents);
	for (UShapeComponent* shape : ShapeComponents)
	{
		shape->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
		shape->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnComponentEndOverlap);
	}

	OffCollisions();
}

void AAttachment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == OwnerCharacter) return;


	if (OnAttachmentBeginOverlap.IsBound())
	{
		ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);
		if(otherCharacter== nullptr) return;

		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter, this, otherCharacter);
	}
}

void AAttachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OnAttachmentEndOverlap.IsBound())
	{
		ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);
		if (otherCharacter == nullptr) return;

		OnAttachmentEndOverlap.Broadcast(OwnerCharacter, this, otherCharacter);
	}
}

void AAttachment::OnCollisions(FString InCollisionName)
{
	if (InCollisionName.Compare("None") == 0)
	{
		for (UShapeComponent* shape : ShapeComponents)
			shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		for (UShapeComponent* shape : ShapeComponents)
		{
			if (shape->GetName().Contains(InCollisionName))
				shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
	}

}

void AAttachment::OffCollisions()
{
	for (UShapeComponent* shape : ShapeComponents)
		shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}