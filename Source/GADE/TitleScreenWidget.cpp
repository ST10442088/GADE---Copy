// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UTitleScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (StartButton != nullptr)
	{
		(*StartButton).OnClicked.RemoveDynamic(this, &UTitleScreenWidget::OnStartClick);
		(*StartButton).OnClicked.AddDynamic(this, &UTitleScreenWidget::OnStartClick);
	}

	if (ExitButton != nullptr)
	{
		(*ExitButton).OnClicked.RemoveDynamic(this, &UTitleScreenWidget::OnExitClick);
		(*ExitButton).OnClicked.AddDynamic(this, &UTitleScreenWidget::OnExitClick);
	}
}

void UTitleScreenWidget::OnStartClick()
{
	UGameplayStatics::OpenLevel(this, gameLevelName);
}

void UTitleScreenWidget::OnExitClick()
{
	APlayerController* playerController = GetOwningPlayer();
	UKismetSystemLibrary::QuitGame(this, playerController, EQuitPreference::Quit, false);
}
