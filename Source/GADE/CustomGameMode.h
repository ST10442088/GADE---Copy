// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SaveGameLeaderboard.h"
#include "CustomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GADE_API ACustomGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	void RespawnCharacter(AController* characterController);
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> botCharacterClass;

	UPROPERTY(BlueprintReadOnly, Category = "Leaderboard")
	TArray<FLeaderboardEntry> currentLeaderboardStandings;

	UFUNCTION(BlueprintCallable)
	void IncreaseKillCount(FName killerName);

	UFUNCTION(BlueprintPure)
	TArray<FLeaderboardEntry> GetFinalLeaderboard() const;

	UFUNCTION(BlueprintPure)
	int32 GetRemainingTime() const;

private:
	 FTimerHandle gameDurationTimer;
	 float timerDelayAndDuration = 300.F;
	 void EndGameSession();
};
