// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FindHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class GADE_API UBTTaskNode_FindHealthPickup : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector healthPickupLocation;

	UPROPERTY(EditAnywhere)
	FName healthPickupTag;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};
