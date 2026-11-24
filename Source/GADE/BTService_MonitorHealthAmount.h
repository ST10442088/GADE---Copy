// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_MonitorHealthAmount.generated.h"

/**
 * 
 */
UCLASS()
class GADE_API UBTService_MonitorHealthAmount : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_MonitorHealthAmount();

protected:

	UPROPERTY()
	UBlackboardComponent* blackboardComponent = nullptr;

	UPROPERTY()
	class ABotCharacter* aiControlledCharacter = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBlackboardKeySelector IsHealthTooLow;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;

	UFUNCTION()
	void OnHealthChange(int32 healthAmount);
};
