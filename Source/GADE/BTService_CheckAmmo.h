// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckAmmo.generated.h"

class ABotCharacter;

/**
 * 
 */
UCLASS()
class GADE_API UBTService_CheckAmmo : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_CheckAmmo();

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;

	UPROPERTY()
	UBlackboardComponent* blackboardComponent = nullptr;

	UPROPERTY()
	ABotCharacter* aiControlledCharacter = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBlackboardKeySelector IsAmmoBelowHalf;

	UFUNCTION()
	void OnAmmoChanged(int32 ammoAmount);
};
