// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveGameLeaderboard.h"
#include "Components/TextBlock.h"
#include "LeaderboardSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class GADE_API ULeaderboardSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetUpRow(const FLeaderboardEntry& leaderboardEntryInfo);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* nameTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* killAmountTextBlock;
};
