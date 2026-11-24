// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BotAIController.h"
#include "PatrolPoints.h"
#include "BotCharacter.h"

UBTTask_FindNextPatrolPoint::UBTTask_FindNextPatrolPoint()
{

}

EBTNodeResult::Type UBTTask_FindNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	ABotAIController* botAIController = Cast<ABotAIController>(OwnerComponent.GetAIOwner());
	if (botAIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APawn* aiControlledPawn = (*botAIController).GetPawn();
	if (aiControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ABotCharacter* aiControlledCharacter = Cast<ABotCharacter>(aiControlledPawn);
	if (aiControlledCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APatrolPoints* patrolPointsActor = (*aiControlledCharacter).patrolPointActor;
	if (patrolPointsActor == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector nextPatrolPoint;
	bool isNextPatrol_PointAvailable = (*patrolPointsActor).GetNextPatrolPoint(nextPatrolPoint);
	if (isNextPatrol_PointAvailable == false)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* blackboardComponent = OwnerComponent.GetBlackboardComponent();
	if (blackboardComponent == nullptr)
	{
		return::EBTNodeResult::Failed;
	}

	(*blackboardComponent).SetValueAsVector(LocationToMoveToKey.SelectedKeyName, nextPatrolPoint);

	return EBTNodeResult::Succeeded;
}
