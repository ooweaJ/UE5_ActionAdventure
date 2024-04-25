#include "Actors/Weapon/Rifle.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ActionComponent.h"

ARifle::ARifle()
{
	KeyValue = "Rifle";
}

void ARifle::BeginPlay()
{
	Super::BeginPlay();
}

void ARifle::Attack()
{
	//UKismetSystemLibrary::LineTraceSingle(GetWorld(), )
}

void ARifle::MouseR()
{
	Action->OnAim();
}

void ARifle::OffMouseR()
{
	Action->OffAim();
}
