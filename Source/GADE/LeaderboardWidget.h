// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeaderboardWidget.generated.h"

class UScrollBox;
class ULeaderboardSlotWidget;
class UButton;
/**
 * 
 */
UCLASS()
class GADE_API ULeaderboardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void UpdateAndRefreshLeaderboard();

	void SetResumeButtonVisible(bool isPauseOrEnd);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* leaderboardScrollBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULeaderboardSlotWidget> leaderboardSlotClass;

	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* TitleScreenButton;

	UFUNCTION()
	void OnResumeButtonClick();

	UFUNCTION()
	void OnRestartButtonClick();

	UFUNCTION()
	void OnTitleScreenButtonClick();

	UPROPERTY()
	FName titleScreenLevelName = "TitleScreen";

};
