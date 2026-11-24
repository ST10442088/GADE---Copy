// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindAmmo.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_FindAmmo::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{

	UBlackboardComponent* blackboardComp = OwnerComponent.GetBlackboardComponent();
	if (blackboardComp == nullptr)
	{
		return::EBTNodeResult::Failed;
	}

	TArray<AActor*> ammoPickupList;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), ammoPickupTag, ammoPickupList);

	if (ammoPickupList.Num() == 0)
	{
		return::EBTNodeResult::Failed;
	}

	const AActor* randomAmmoPickup = ammoPickupList[FMath::RandRange(0, ammoPickupList.Num() - 1)];
	(*blackboardComp).SetValueAsVector(ammoKey.SelectedKeyName, (*randomAmmoPickup).GetActorLocation());

	return EBTNodeResult::Succeeded;
}
