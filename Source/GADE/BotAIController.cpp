// Fill out your copyright notice in the Description page of Project Settings.


#include "BotAIController.h"
#include "Perception/AIPerceptionComponent.h" 
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

ABotAIController::ABotAIController()
{
	const auto sightSenseConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Sense Configuration");
	(*sightSenseConfig).SightRadius = 800.f;
	(*sightSenseConfig).LoseSightRadius = 1000.f;
	(*sightSenseConfig).PeripheralVisionAngleDegrees = 45.f;
	(*sightSenseConfig).DetectionByAffiliation.bDetectEnemies = true;
	(*sightSenseConfig).DetectionByAffiliation.bDetectFriendlies = true;
	(*sightSenseConfig).DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("Perception Component");
	(*PerceptionComponent).ConfigureSense(*sightSenseConfig);
	(*PerceptionComponent).SetDominantSense((*sightSenseConfig).GetSenseImplementation());
	(*PerceptionComponent).AgeStimuli(4.f);
	(*PerceptionComponent).OnTargetPerceptionUpdated.AddDynamic(this, &ABotAIController::OnTargetPerceptionUpdate);
}

void ABotAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
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

/* void ABotAIController::OnTargetPerceptionUpdate(AActor* actor, FAIStimulus AIStimulus)
{
	UBlackboardComponent* blackboardComponent = GetBlackboardComponent();
	if (!blackboardComponent) return;

	FAISenseID senseID = UAISense::GetSenseID<UAISense_Sight>();
	if (AIStimulus.Type != senseID) return;

	if (ACharacter* detectedCharacter = Cast<ACharacter>(actor))
	{
		if (AIStimulus.WasSuccessfullySensed())
		{
			UObject* currentEnemy = blackboardComponent->GetValueAsObject(FName("EnemyEntity"));
			if (currentEnemy != detectedCharacter)
			{
				if (AActor* oldEnemyActor = Cast<AActor>(currentEnemy))
				{
					oldEnemyActor->OnDestroyed.RemoveDynamic(this, &ABotAIController::HandleEnemyDestroyed);
				}

				detectedCharacter->OnDestroyed.AddUniqueDynamic(this, &ABotAIController::HandleEnemyDestroyed);
				blackboardComponent->SetValueAsObject(FName("EnemyEntity"), detectedCharacter);
				SetFocus(detectedCharacter);
			}
		}
		else
		{
			if (blackboardComponent->GetValueAsObject(FName("EnemyEntity")) == detectedCharacter)
			{
				detectedCharacter->OnDestroyed.RemoveDynamic(this, &ABotAIController::HandleEnemyDestroyed);
				blackboardComponent->ClearValue(FName("EnemyEntity"));
				ClearFocus(EAIFocusPriority::Gameplay);
			}
		}
	}
}

void ABotAIController::HandleEnemyDestroyed(AActor* DestroyedActor)
{
	if (UBlackboardComponent* blackboardComponent = GetBlackboardComponent())
	{
		if (blackboardComponent->GetValueAsObject(FName("EnemyEntity")) == DestroyedActor)
		{
			blackboardComponent->ClearValue(FName("EnemyEntity"));
			ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}*/

