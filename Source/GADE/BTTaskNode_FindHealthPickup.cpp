// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindHealthPickup.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTaskNode_FindHealthPickup::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	UBlackboardComponent* blackboardComp = OwnerComponent.GetBlackboardComponent();
	if (blackboardComp == nullptr)
	{
		return::EBTNodeResult::Failed;
	}

	TArray<AActor*> healthPickupList;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), healthPickupTag, healthPickupList);

	if (healthPickupList.Num() == 0)
	{
		return::EBTNodeResult::Failed;
	}

	const AActor* randomHealthPickup = healthPickupList[FMath::RandRange(0, healthPickupList.Num() - 1)];
	(*blackboardComp).SetValueAsVector(healthPickupLocation.SelectedKeyName, (*randomHealthPickup).GetActorLocation());

	return EBTNodeResult::Succeeded;
}
