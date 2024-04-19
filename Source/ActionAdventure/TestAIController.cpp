// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAIController.h"
#include "BehaviorTree/BehaviorTree.h"

ATestAIController::ATestAIController()
{

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/_dev/BT_AIDefault.BT_AIDefault'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void ATestAIController::OnPossess(APawn* InPawn)
{
	RunBehaviorTree(BTAsset);
}
