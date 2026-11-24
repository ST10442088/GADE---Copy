// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TitleScreenGameMode.generated.h"
class UTitleScreenWidget;
/**
 * 
 */
UCLASS()
class GADE_API ATitleScreenGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATitleScreenGameMode();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTitleScreenWidget> titleScreenWidgetClass;

};
