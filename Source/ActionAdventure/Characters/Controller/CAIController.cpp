#include "Characters/Controller/CAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

#include "Components/BehaviorComponent.h"
#include "Characters/AI/AICharacter.h"
#include "GameFrameWork/Character.h"
#include "Engine.h"

ACAIController::ACAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard");
	Behavior = CreateDefaultSubobject<UBehaviorComponent>("Behavior");
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
	
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 1000.f;
	Sight->LoseSightRadius = 1000.f;
	Sight->PeripheralVisionAngleDegrees = 360.0f;
	Sight->SetMaxAge(2.f);

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(Sight->GetSenseImplementation());

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Script/AIModule.BlackboardData'/Game/_dev/BB_AIDefault.BB_AIDefault'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/_dev/BT_AIDefault.BT_AIDefault'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void ACAIController::SetLoactionKey(FVector InLoaction)
{
	Blackboard->SetValueAsVector("Location", InLoaction);
}

void ACAIController::SetTargetKey(ACharacter* InCharacter)
{
	Blackboard->SetValueAsObject("Target", InCharacter);
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	OwnerAI = Cast<AAICharacter>(InPawn);
	if (!OwnerAI) return;
	UBlackboardComponent* BlackboardPtr = Blackboard;

	UseBlackboard(BBAsset, BlackboardPtr);

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);

	Behavior->SetBlackBoard(Blackboard);
	RunBehaviorTree(BTAsset);
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();

	Perception->OnPerceptionUpdated.Clear();

}

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	ACharacter* player = nullptr;
	for (AActor* actor : actors)
	{
		player = Cast<ACharacter>(actor);

		if (!!player)
			break;
	}

	Blackboard->SetValueAsObject("Target", player);
}
