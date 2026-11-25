// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"

void AMyPlayerController::ShowLeaderboardOnPause()
{
	if (currentUIState == EUIStates::Playing)
	{
		SwitchUIState(EUIStates::Paused);
	}

	else if (currentUIState == EUIStates::Paused)
	{
		SwitchUIState(EUIStates::Playing);
	}
}

void AMyPlayerController::ShowEndGameLeaderboard()
{
	SwitchUIState(EUIStates::MatchOver);
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

void AMyPlayerController::SwitchUIState(EUIStates newUIstate)
{
	if (currentUIState == newUIstate) { return; }

	if (currentUIState == EUIStates::Paused)
	{
		if (activeLeaderboard != nullptr)
		{
			(*activeLeaderboard).RemoveFromParent();
			activeLeaderboard = nullptr;
		}
	}

	currentUIState = newUIstate;
	if (currentUIState == EUIStates::Paused)
	{
		if (leaderboardWidgetClass != nullptr && activeLeaderboard == nullptr)
		{
			activeLeaderboard = CreateWidget<ULeaderboardWidget>(this, leaderboardWidgetClass);

			if (activeLeaderboard != nullptr)
			{
				(*activeLeaderboard).AddToViewport();
				(*activeLeaderboard).SetResumeButtonVisible(true);

				SetPause(true);
				bShowMouseCursor = true;
				SetInputMode(FInputModeGameAndUI());
			}
		}
	}


	else if (currentUIState == EUIStates::Playing)
	{
		SetPause(false);
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}

	else if (currentUIState == EUIStates::MatchOver)
	{
		if (leaderboardWidgetClass != nullptr && activeLeaderboard == nullptr)
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

	currentUIState = EUIStates::Paused;
	SwitchUIState(EUIStates::Playing);

}
