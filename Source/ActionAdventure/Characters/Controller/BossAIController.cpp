#include "Characters/Controller/BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

#include "Components/BossBehaviorComponent.h"
#include "Characters/AI/AIBoss.h"
#include "GameFrameWork/Character.h"
#include "Kismet/GameplayStatics.h"

ABossAIController::ABossAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard");
	Behavior = CreateDefaultSubobject<UBossBehaviorComponent>("Behavior");

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Script/AIModule.BlackboardData'/Game/_dev/Characters/Boss/BB_Boss.BB_Boss'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/_dev/Characters/Boss/BT_Boss.BT_Boss'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void ABossAIController::SetLoactionKey(FVector InLoaction)
{
	Blackboard->SetValueAsVector("Location", InLoaction);
}

void ABossAIController::SetTargetKey(ACharacter* InCharacter)
{
	Blackboard->SetValueAsObject("Target", InCharacter);
}

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();
	
	Blackboard->SetValueAsObject("Target", UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SetLoactionKey(FVector::ZeroVector);
	
}

void ABossAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerAI = Cast<AAIBoss>(InPawn);
	if (!OwnerAI) return;
	UBlackboardComponent* BlackboardPtr = Blackboard;

	UseBlackboard(BBAsset, BlackboardPtr);

	Behavior->SetBlackBoard(Blackboard);
	RunBehaviorTree(BTAsset);
}

void ABossAIController::OnUnPossess()
{
}

void ABossAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
}
