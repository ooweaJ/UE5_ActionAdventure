#include "Components/DissolveComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
#include "GameFrameWork/Character.h"

UDissolveComponent::UDissolveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	{
		ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> Asset(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/_dev/Materials/M_DissolveEffect_Inst.M_DissolveEffect_Inst'"));
		if (Asset.Succeeded())
		{
			Material = Asset.Object;
		}
	}

	{
		ConstructorHelpers::FObjectFinder<UCurveFloat> Asset(TEXT("/Script/Engine.CurveFloat'/Game/_dev/Dissolve.Dissolve'"));
		if (Asset.Succeeded())
		{
			Curve = Asset.Object;
		}
	}
}

void UDissolveComponent::BeginPlay()
{
	Super::BeginPlay();

	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);

	FOnTimelineFloat startTimeline;
	startTimeline.BindUFunction(this, "OnStartTimeline");
	Timeline.AddInterpFloat(Curve, startTimeline);
	Timeline.SetPlayRate(PlayRate);
}

void UDissolveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Timeline.IsPlaying())
		Timeline.TickTimeline(DeltaTime);

}

void UDissolveComponent::Play()
{
	Timeline.PlayFromStart();
}

void UDissolveComponent::Stop()
{
	Timeline.Stop();
}

void UDissolveComponent::OnStartTimeline(float Output)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	USkeletalMeshComponent* CharacterMesh = character->GetMesh();

	// 메시에 적용된 모든 머티리얼을 가져옵니다.
	const TArray<UMaterialInterface*>& Materials = CharacterMesh->GetMaterials();

	// 메시에 적용된 머티리얼의 개수를 출력합니다.
	int32 NumMaterials = Materials.Num();

	if (character == nullptr) return;
	// 모든 머티리얼에 대해 반복문을 돌며 작업을 수행할 수 있습니다.
	for (int32 Index = 0; Index < NumMaterials; ++Index)
	{
		if (character->GetMesh() == nullptr) return;
		character->GetMesh()->SetMaterial(Index, DynamicMaterial);
	}

	DynamicMaterial->SetScalarParameterValue("amount", Output);
}

