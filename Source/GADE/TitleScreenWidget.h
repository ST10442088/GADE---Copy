// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleScreenWidget.generated.h"
class UButton;
/**
 * 
 */
UCLASS()
class GADE_API UTitleScreenWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY()
	FName gameLevelName = "Level";

private:
	UFUNCTION()
	void OnStartClick();

	UFUNCTION()
	void OnExitClick();

};
