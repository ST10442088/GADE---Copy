// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickupActor.h"
#include "HealthComponent.h"
#include "GameCharacter.h"
#include "BotCharacter.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"

// Sets default values
AHealthPickupActor::AHealthPickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	healthPickupCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Health Collider"));
	RootComponent = healthPickupCollider;

	(*healthPickupCollider).OnComponentBeginOverlap.AddDynamic(this, &AHealthPickupActor::OnPickupOverlap);

}

// Called when the game starts or when spawned
void AHealthPickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHealthPickupActor::EnablePickup()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
	(*GetWorld()).GetTimerManager().ClearTimer(disablingTimer);
}

void AHealthPickupActor::ActivateDisablingTimer()
{	
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	(*GetWorld()).GetTimerManager().SetTimer(disablingTimer, this, &AHealthPickupActor::EnablePickup, 8.f, false);

}


void AHealthPickupActor::OnPickupOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UHealthComponent* healthComponent = (*OtherActor).FindComponentByClass<UHealthComponent>())
	{
		(*healthComponent).Health = (*healthComponent).Health + 30;
		(*healthComponent).HealthAmountChange.Broadcast((*healthComponent).Health);
		ActivateDisablingTimer();

		if ((*healthComponent).Health > 100)
		{
			(*healthComponent).Health = 100;
		}
	}
}

