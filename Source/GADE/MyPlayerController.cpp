// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"

void AMyPlayerController::ShowLeaderboardOnPause()
{
	if (leaderboardWidgetClass != nullptr && activeLeaderboard == nullptr)
	{
		activeLeaderboard = CreateWidget<ULeaderboardWidget>(this, leaderboardWidgetClass);
		if (activeLeaderboard != nullptr)
		{
			(*activeLeaderboard).AddToViewport();
			SetPause(true);
			bShowMouseCursor = true;
			SetInputMode(FInputModeGameAndUI());
		}

	}
	
	
	
    else if (activeLeaderboard != nullptr)
		{
			(*activeLeaderboard).RemoveFromParent();
			activeLeaderboard = nullptr;
			SetPause(false);
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
		}
}

void AMyPlayerController::ShowEndGameLeaderboard()
{
	hasMatchEnded = true;
	if (activeLeaderboard != nullptr)
	{
		(*activeLeaderboard).RemoveFromParent();
		activeLeaderboard = nullptr;
	}

	if (leaderboardWidgetClass != nullptr)
	{
		activeLeaderboard = CreateWidget<ULeaderboardWidget>(this, leaderboardWidgetClass);
		if (activeLeaderboard != nullptr)
		{
			(*activeLeaderboard).AddToViewport();
			(*activeLeaderboard).SetResumeButtonVisible(false);
			UGameplayStatics::SetGamePaused(GetWorld(), true);
			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (enhancedInputComponent != nullptr)
	{
		if (IA_Pause != nullptr)
		{
			(*enhancedInputComponent).BindAction(IA_Pause, ETriggerEvent::Triggered, this, &AMyPlayerController::ShowLeaderboardOnPause);
		}
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
	if (UEnhancedInputLocalPlayerSubsystem* enhancedLocalSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (IMC_Character != nullptr)
		{
			(*enhancedLocalSystem).AddMappingContext(IMC_Character, 1);
		}
	}
}
