#include "Actors/BossRange.h"
#include "Characters/Players/CPlayer.h"
#include "Engine/DamageEvents.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ABossRange::ABossRange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    {
        ConstructorHelpers::FObjectFinder<UNiagaraSystem> Asset(TEXT("/Script/Niagara.NiagaraSystem'/Game/sA_Megapack_v1/sA_SkillSet_1/Fx/NiagaraSystems/NS_Thorn_3.NS_Thorn_3'"));
        if (Asset.Succeeded())
            Niagara = Asset.Object;
    }
}

// Called when the game starts or when spawned
void ABossRange::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossRange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossRange::SpawnAttack()
{
    // 스피어 트레이스의 파라미터 설정
    FCollisionQueryParams TraceParams(FName(TEXT("SphereTrace")), true, this);
    TraceParams.bReturnPhysicalMaterial = false;

    // 스피어 트레이스 시작 위치와 끝 위치 설정
    FVector StartLocation = GetActorLocation();
    FVector EndLocation = StartLocation + FVector(0, 0, 1); // 여기서 높이는 필요에 따라 조정할 수 있습니다.

    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, StartLocation);

    // 스피어 트레이스 수행
    TArray<FHitResult> HitResults;
    GetWorld()->SweepMultiByObjectType(
        HitResults,
        StartLocation,
        EndLocation,
        FQuat::Identity,
        FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllObjects),
        FCollisionShape::MakeSphere(250.0f), // 반지름이 100인 스피어 생성
        TraceParams
    );

    // 검출된 모든 오브젝트에 대한 처리
    for (const FHitResult& Hit : HitResults)
    {
        // ACPlayer 타입의 오브젝트인지 확인
        if (Hit.GetActor() != nullptr && Hit.GetActor()->IsA<ACPlayer>())
        {
            // ACPlayer 타입의 오브젝트를 검출한 경우에 수행할 작업을 여기에 추가합니다.
            ACPlayer* Player = Cast<ACPlayer>(Hit.GetActor());
            if (Player != nullptr)
            {
                FDamageEvent DamageEvent;
                Player->TakeDamage(20.f, DamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
            }
        }
    }
}

