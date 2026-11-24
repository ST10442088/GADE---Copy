// Fill out your copyright notice in the Description page of Project Settings.


#include "LeaderboardSlotWidget.h"

void ULeaderboardSlotWidget::SetUpRow(const FLeaderboardEntry& leaderboardEntryInfo)
{
	if (nameTextBlock != nullptr)
	{
		(*nameTextBlock).SetText(FText::FromString(leaderboardEntryInfo.entryName));
	}

	if (killAmountTextBlock != nullptr)
	{
		(*killAmountTextBlock).SetText(FText::AsNumber(leaderboardEntryInfo.killAmount));
	}
}
