// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindAmmo.generated.h"

/**
 * 
 */
UCLASS()
class GADE_API UBTTask_FindAmmo : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector ammoKey;

	UPROPERTY(EditAnywhere)
	FName ammoPickupTag;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	
};
