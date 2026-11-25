// Fill out your copyright notice in the Description page of Project Settings.


#include "BotCharacter.h"
#include "WeaponComponent.h"
#include "PatrolPoints.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABotCharacter::ABotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	weaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Gun Component"));
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void ABotCharacter::BeginPlay()
{
	Super::BeginPlay();
	patrolPointActor = Cast<APatrolPoints>(UGameplayStatics::GetActorOfClass(GetWorld(), APatrolPoints::StaticClass()));

}

// Called every frame
void ABotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


