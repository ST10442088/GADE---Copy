// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotAIController.generated.h"

struct FAIStimulus;
struct FActorPerceptionUpdateInfo;
/**
 * 
 */
UCLASS()
class GADE_API ABotAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABotAIController();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> BotBehaviorTree;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void OnTargetPerceptionUpdate(AActor* actor, FAIStimulus AIStimulus);

	void HandleEnemyDestroyed(AActor* DestroyedActor);
};
