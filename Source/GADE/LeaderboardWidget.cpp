// Fill out your copyright notice in the Description page of Project Settings.


#include "LeaderboardWidget.h"
#include "LeaderboardSlotWidget.h"
#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"
#include "CustomGameMode.h"
#include "Components/Button.h"
#include "MyPlayerController.h"


void ULeaderboardWidget::UpdateAndRefreshLeaderboard()
{
	if (leaderboardScrollBox == nullptr || leaderboardSlotClass == nullptr) return;

	(*leaderboardScrollBox).ClearChildren();

	ACustomGameMode* gameMode = Cast<ACustomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gameMode == nullptr) return;


	TArray<FLeaderboardEntry> SortedLeaderboardEntries = (*gameMode).GetFinalLeaderboard();

	for (const FLeaderboardEntry& leaderboardEntry : SortedLeaderboardEntries)
	{
		ULeaderboardSlotWidget* newestSlot = CreateWidget<ULeaderboardSlotWidget>(this, leaderboardSlotClass);
		if (newestSlot != nullptr)
		{	
			(*leaderboardScrollBox).AddChild(newestSlot);
			(*newestSlot).SetUpRow(leaderboardEntry);
		}
	}
}

void ULeaderboardWidget::SetResumeButtonVisible(bool isPauseOrEnd)
{

	if (ResumeButton != nullptr)
	{
		if (isPauseOrEnd == true)
		{
			(*ResumeButton).SetVisibility(ESlateVisibility::Visible);
		}

		else
		{
		  (*ResumeButton).SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}


void ULeaderboardWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateAndRefreshLeaderboard();

	if (ResumeButton != nullptr)
	{
		(*ResumeButton).OnClicked.RemoveDynamic(this, &ULeaderboardWidget::OnResumeButtonClick);
		(*ResumeButton).OnClicked.AddDynamic(this, &ULeaderboardWidget::OnResumeButtonClick);
	}

	if (RestartButton != nullptr)
	{
		(*RestartButton).OnClicked.RemoveDynamic(this, &ULeaderboardWidget::OnRestartButtonClick);
		(*RestartButton).OnClicked.AddDynamic(this, &ULeaderboardWidget::OnRestartButtonClick);
	}
}

void ULeaderboardWidget::OnResumeButtonClick()
{
	if (AMyPlayerController* playerController = Cast<AMyPlayerController>(GetOwningPlayer()))
	{
		(*playerController).ShowLeaderboardOnPause();
	}
}

void ULeaderboardWidget::OnRestartButtonClick()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	FName currentLevelName = FName(UGameplayStatics::GetCurrentLevelName(GetWorld()));
	UGameplayStatics::OpenLevel(this, currentLevelName);
}
