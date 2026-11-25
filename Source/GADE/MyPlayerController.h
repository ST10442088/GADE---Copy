// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LeaderboardWidget.h"
#include "MyPlayerController.generated.h"

UENUM(BlueprintType)
enum class EUIStates : uint8
{
	Playing, Paused, MatchOver
};

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

	void SwitchUIState(EUIStates newUIstate);

private:
	EUIStates currentUIState = EUIStates::Playing;

protected:
	virtual void BeginPlay() override;

};
