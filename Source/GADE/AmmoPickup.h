// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutomaticGunPickup.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class GADE_API AAmmoPickup : public AAutomaticGunPickup
{
	GENERATED_BODY()


public:
	AAmmoPickup();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapPickup(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
