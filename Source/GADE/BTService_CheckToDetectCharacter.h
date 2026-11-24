// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckToDetectCharacter.generated.h"

/**
 * 
 */
class ABotCharacter;

UCLASS()
class GADE_API UBTService_CheckToDetectCharacter : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_CheckToDetectCharacter();

protected:

	UPROPERTY()
	UBlackboardComponent* blackboardComponent = nullptr;

	UPROPERTY()
	ABotCharacter* aiControlledCharacter = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBlackboardKeySelector IsCharacterDetected;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float sphereRadius = 500.f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory, float DeltaSeconds) override;
};
