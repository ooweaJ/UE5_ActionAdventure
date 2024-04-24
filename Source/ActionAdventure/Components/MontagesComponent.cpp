// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MontagesComponent.h"
#include "GameFramework/Character.h"
#include "Components/StatusComponent.h"
#include "Engine.h"

UMontagesComponent::UMontagesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	{
		ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/_dev/Data/DT_Montage.DT_Montage'"));
		if (Asset.Succeeded())
		{
			DataTable = Asset.Object;
		}
	}
}


// Called when the game starts
void UMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UMontagesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMontagesComponent::PlayKnockBack()
{
	PlayAnimMontage("KnockBack");
}

void UMontagesComponent::PlayAnimMontage(FName Key)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	FMontageData* data = DataTable->FindRow<FMontageData>(Key, "");
	if (!data) return;

	UStateComponent* state = character->GetComponentByClass<UStateComponent>();
	UStatusComponent* status = character->GetComponentByClass<UStatusComponent>();

	if (!data->AnimMontage) return;
	character->StopAnimMontage();
	state->ChangeType(data->Type);
	data->bCanMove ? status->SetMove() : status->SetStop();
	character->PlayAnimMontage(data->AnimMontage, data->PlayRate, data->StartSection);
}

