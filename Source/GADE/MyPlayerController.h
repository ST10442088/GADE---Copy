// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LeaderboardWidget.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GADE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void ShowLeaderboardOnPause();

	UFUNCTION()
	void ShowEndGameLeaderboard();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULeaderboardWidget> leaderboardWidgetClass;

	ULeaderboardWidget* activeLeaderboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* IMC_Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_Pause;

	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;

	bool hasMatchEnded = false;

};
