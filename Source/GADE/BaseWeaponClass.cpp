// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponClass.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Bullet.h"

// Sets default values
ABaseWeaponClass::ABaseWeaponClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	(*GunMesh).SetCollisionProfileName(FName(TEXT("NoCollision")));

	bulletSpawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Arrow"));
	(*bulletSpawnArrow).SetupAttachment(GunMesh);
}

// Called when the game starts or when spawned
void ABaseWeaponClass::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABaseWeaponClass::FireBullets()
{
	FVector bulletSpawnPosition = (*bulletSpawnArrow).GetComponentLocation();

	FRotator bulletRotation = (*bulletSpawnArrow).GetForwardVector().Rotation();

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawnParams.Owner = this;
	spawnParams.Instigator = Cast<APawn>(GetOwner());

	if (spawnParams.Instigator != nullptr)
	{

	    ABullet* bullet = (*GetWorld()).SpawnActor<ABullet>(bulletClass, bulletSpawnPosition, bulletRotation, spawnParams);

	    if (bullet != nullptr && (*bullet).GetRootComponent())
	    {	
			UPrimitiveComponent* collisionComponent = Cast<UPrimitiveComponent>((*bullet).GetRootComponent());
			(*collisionComponent).IgnoreActorWhenMoving(this, true);
			(*collisionComponent).IgnoreActorWhenMoving(spawnParams.Instigator, true);
	    }

	    if (OnNewAmmoAmount.IsBound() == true)
	    {
	       OnNewAmmoAmount.Broadcast(currentAmmoAmount);
     	}
	}


}

void ABaseWeaponClass::ImplementActiveState(bool isWeaponActive)
{
	SetActorHiddenInGame(isWeaponActive == false);
	SetActorEnableCollision(isWeaponActive == true);
	SetActorTickEnabled(isWeaponActive == true);
}

