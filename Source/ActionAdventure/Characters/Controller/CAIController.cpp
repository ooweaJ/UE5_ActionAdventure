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
	//Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard");
	Behavior = CreateDefaultSubobject<UBehaviorComponent>("Behavior");
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
	
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 1000.f;
	Sight->LoseSightRadius = 1000.f;
	Sight->PeripheralVisionAngleDegrees = 180.0f;
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

void ACAIController::BeginPlay()
{

}

void ACAIController::Tick(float DeltaTime)
{

}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	RunBehaviorTree(BTAsset);

	//OwnerAI = Cast<AAICharacter>(InPawn);
	//if (!OwnerAI) return;
	//UBlackboardComponent* BlackboardPtr = Blackboard;

	//UseBlackboard(OwnerAI->GetBehaviorTree()->BlackboardAsset, BlackboardPtr);

	//Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);

	//Behavior->SetBlackBoard(Blackboard);
	//RunBehaviorTree(OwnerAI->GetBehaviorTree());
	//GEngine->AddOnScreenDebugMessage(0, 1, FColor::Black, "Hi");
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
