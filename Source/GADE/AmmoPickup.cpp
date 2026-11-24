// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickup.h"
#include "WeaponComponent.h"
#include "Components/SphereComponent.h"
#include "GameCharacter.h"

AAmmoPickup::AAmmoPickup()
{
	
}


void AAmmoPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AAmmoPickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UWeaponComponent* weaponComponent = (*OtherActor).FindComponentByClass<UWeaponComponent>())
	{
		(*weaponComponent).RefillAmmo();
		if ((*weaponComponent).RefillAmmo() == true)
		{
			Destroy();
		}
	}
}

