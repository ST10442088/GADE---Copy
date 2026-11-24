// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameLeaderboard.generated.h"

USTRUCT(BlueprintType)
struct FLeaderboardEntry
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	FString entryName;

	UPROPERTY(BlueprintReadWrite)
	int32 killAmount;
	bool operator<(const FLeaderboardEntry& OtherLeaderboardEntry) const
	{
		return killAmount > OtherLeaderboardEntry.killAmount;
	}
};


/**
 * 
 */
UCLASS()
class GADE_API USaveGameLeaderboard : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TArray<FLeaderboardEntry> SavedLeaderboardEntries;

	UPROPERTY(VisibleAnywhere)
	FString SaveSlotName = TEXT("LeaderboardSaveSlot");

	UPROPERTY(VisibleAnywhere)
	int32 userIndex = 0;


	
};
