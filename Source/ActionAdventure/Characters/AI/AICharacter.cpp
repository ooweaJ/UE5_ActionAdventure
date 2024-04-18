#include "Characters/AI/AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


#include "Characters/CAnimInstance.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/MoveComponent.h"
#include "Components/EquipComponent.h"

AAICharacter::AAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_carla_rigged_001_ue4/rp_carla_rigged_001_ue4.rp_carla_rigged_001_ue4'"));
		if (!Asset.Succeeded()) return;
		Meshs.Add(Asset.Object);
	}
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_claudia_rigged_002_ue4/rp_claudia_rigged_002_ue4.rp_claudia_rigged_002_ue4'"));
		if (!Asset.Succeeded()) return;
		Meshs.Add(Asset.Object);
	}
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_eric_rigged_001_ue4/rp_eric_rigged_001_ue4.rp_eric_rigged_001_ue4'"));
		if (!Asset.Succeeded()) return;
		Meshs.Add(Asset.Object);
	}
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_nathan_rigged_003_ue4/rp_nathan_rigged_003_ue4.rp_nathan_rigged_003_ue4'"));
		if (!Asset.Succeeded()) return;
		Meshs.Add(Asset.Object);
	}
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_sophia_rigged_003_ue4/rp_sophia_rigged_003_ue4.rp_sophia_rigged_003_ue4'"));
		if (!Asset.Succeeded()) return;
		Meshs.Add(Asset.Object);
	}

	USkeletalMeshComponent* mesh = GetMesh();
	mesh->SetRelativeLocation(FVector(0, 0, -88));
	mesh->SetRelativeRotation(FRotator(0, -90, 0));

	int32 Random = FMath::RandRange(0, Meshs.Num() - 1);
	mesh->SetSkeletalMesh(Meshs[Random]);
	{
		ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset{ TEXT("/Script/Engine.AnimBlueprint'/Game/_dev/Characters/Players/ABP_AI.ABP_AI_C'") };
		check(AnimAsset.Class);
		mesh->SetAnimInstanceClass(AnimAsset.Class);
	}

	{
		StatusComponent = CreateDefaultSubobject<UStatusComponent>("StatusComponent");
		StateComponent = CreateDefaultSubobject<UStateComponent>("StateComponent");
		MoveComponent = CreateDefaultSubobject<UMoveComponent>("MoveComponent");
		ActionComponent = CreateDefaultSubobject<UActionComponent>("ActionComponent");
		EquipComponent = CreateDefaultSubobject<UEquipComponent>("Equip");
	}

}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

