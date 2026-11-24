// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShootOtherEntities.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BotAIController.h"
#include "BotCharacter.h"
#include "WeaponComponent.h"
#include "TimerManager.h"

EBTNodeResult::Type UBTTask_ShootOtherEntities::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	ABotAIController* botAIController = Cast<ABotAIController>(OwnerComponent.GetAIOwner());
	if (botAIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ABotCharacter* aiControlledCharacter = Cast<ABotCharacter>((*botAIController).GetPawn());
	if (aiControlledCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	aiControlledCharacter->weaponComponent->FireBulletsWithEquippedWeapon();
	return EBTNodeResult::Succeeded;
}
