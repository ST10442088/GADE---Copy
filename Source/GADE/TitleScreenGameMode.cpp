// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenGameMode.h"
#include "TitleScreenWidget.h"
#include "Kismet/GameplayStatics.h"

ATitleScreenGameMode::ATitleScreenGameMode()
{
	DefaultPawnClass = nullptr;
}

void ATitleScreenGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController != nullptr && titleScreenWidgetClass != nullptr)
	{
		UTitleScreenWidget* titleScreen = CreateWidget<UTitleScreenWidget>(playerController, titleScreenWidgetClass);
		if (titleScreen != nullptr)
		{
			(*titleScreen).AddToViewport();
			(*playerController).bShowMouseCursor = true;
			(*playerController).SetInputMode(FInputModeUIOnly());
		}

	}
}
