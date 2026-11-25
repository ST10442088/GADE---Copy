// Fill out your copyright notice in the Description page of Project Settings.


#include "BotAIController.h"
#include "Perception/AIPerceptionComponent.h" 
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

ABotAIController::ABotAIController()
{

}

void ABotAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UBlackboardComponent* blackboardComponent = GetBlackboardComponent())
	{
		(*blackboardComponent).SetValueAsBool(TEXT("IsHealthTooLow"), false);
		(*blackboardComponent).ClearValue(TEXT("EnemyEntity"));
		(*blackboardComponent).ClearValue(TEXT("LocationToMoveToKey"));
		(*blackboardComponent).ClearValue(TEXT("HealthPickupLocation"));
	}

    if (ensureMsgf(BotBehaviorTree, TEXT("Behavior Tree is nullptr! Please assign BehaviorTree in your AI Controller.")))
	{
		RunBehaviorTree(BotBehaviorTree);
	}

    if (ACharacter* botCharacter = Cast<ACharacter>(InPawn))
    {
        if (USkeletalMeshComponent* botMesh = (*botCharacter).GetMesh())
        {
            if (botMaterial == nullptr)
            {
                botMaterial = (*botMesh).GetMaterial(0);
            }

            else
            {
                (*botMesh).SetMaterial(0, botMaterial);
            }
        }
    }
}


