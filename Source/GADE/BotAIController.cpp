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
}

void ABotAIController::OnTargetPerceptionUpdate(AActor* actor, FAIStimulus AIStimulus)
{
	UBlackboardComponent* blackboardComponent = GetBlackboardComponent();
	FAISenseID  senseID = UAISense::GetSenseID<UAISense_Sight>();
	if (ACharacter* detectedCharacter = Cast<ACharacter>(actor))
	{
	    if (AIStimulus.Type == senseID && AIStimulus.WasSuccessfullySensed())
	    {
		   (*blackboardComponent).SetValueAsObject(FName("EnemyEntity"), detectedCharacter);
		   SetFocus(detectedCharacter);
    	}

		else
		{
			if ((*blackboardComponent).GetValueAsObject("EnemyEntity") == detectedCharacter)
			{
				(*blackboardComponent).ClearValue(FName("EnemyEntity"));
				ClearFocus(EAIFocusPriority::Gameplay);
			}
		}
	}

}


