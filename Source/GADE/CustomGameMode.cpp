// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/Controller.h"
#include "AIController.h"
#include "TimerManager.h"
#include "MyPlayerController.h"

void ACustomGameMode::RespawnCharacter(AController* characterController)
{
	if (characterController == nullptr) { return; }

	TSubclassOf<APawn> pawnClassToSpawn = DefaultPawnClass;
	if ((*characterController).IsA(AAIController::StaticClass()) == true)
	{
		pawnClassToSpawn = botCharacterClass;
	}

	if (pawnClassToSpawn == nullptr) { return; }

	TArray<AActor*> respawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), respawnPoints);

	if (respawnPoints.Num() > 0)
	{
		int32 randomSpawnPointIndex = FMath::RandRange(0, respawnPoints.Num() - 1);
		AActor* spawnPointActor = respawnPoints[randomSpawnPointIndex];

		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FVector characterSpawnLocation = (*spawnPointActor).GetActorLocation();
		FRotator characterRotation = (*spawnPointActor).GetActorRotation();

		APawn* pawnToBeSpawned = (*GetWorld()).SpawnActor<APawn>(pawnClassToSpawn, characterSpawnLocation, characterRotation, spawnParams);
		if (pawnToBeSpawned != nullptr)
		{
			(*characterController).Possess(pawnToBeSpawned);
		}
	}
}

void ACustomGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<FString> GameEntities = { "Player", "Bot 1", "Bot 2", "Bot 3", "Bot 4" };

	for (const FString& entityName : GameEntities)
	{
		FLeaderboardEntry latestEntry;
		latestEntry.entryName = entityName;
		latestEntry.killAmount = 0;
		currentLeaderboardStandings.Add(latestEntry);
	}	
	GetWorldTimerManager().SetTimer(gameDurationTimer, this, &ACustomGameMode::EndGameSession, timerDelayAndDuration, false);
}

void ACustomGameMode::IncreaseKillCount(FName killerName)
{
	for (FLeaderboardEntry& leaderboardEntry : currentLeaderboardStandings)
	{
		if (leaderboardEntry.entryName == killerName)
		{
			leaderboardEntry.killAmount++;
		}
	}	

}


TArray<FLeaderboardEntry> ACustomGameMode::GetFinalLeaderboard() const
{
	TArray<FLeaderboardEntry> sortedLeaderboard = currentLeaderboardStandings;
	sortedLeaderboard.Sort();
	return sortedLeaderboard;
}

int32 ACustomGameMode::GetRemainingTime() const
{
	if (GetWorldTimerManager().IsTimerActive(gameDurationTimer))
	{
		return GetWorldTimerManager().GetTimerRemaining(gameDurationTimer);
	}
	return 0;
}


void ACustomGameMode::EndGameSession()
{
	if (AMyPlayerController* playerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		(*playerController).ShowEndGameLeaderboard();
	}
}
