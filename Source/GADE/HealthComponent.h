// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, int32, NewHealthAmount);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GADE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditDefaultsOnly)
	float Health = 100.f;

	UFUNCTION()
	void DrainHealth(AActor* damagedActor, float healthAmountLost, const UDamageType* damageType, AController* InstigatedBy, AActor* damageBringer);

	UPROPERTY()
	FOnHealthChanged HealthAmountChange;
private:
	TArray<FName> desiredTags = { "Player", "Bot 1", "Bot 2", "Bot 3", "Bot 4" };
};
