// Fill out your copyright notice in the Description page of Project Settings.


#include "AutomaticGunPickup.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "WeaponComponent.h"

AAutomaticGunPickup::AAutomaticGunPickup()
{
	autoGunCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Gun Collider"));
	RootComponent = autoGunCollider;
	(*GunMesh).SetupAttachment(autoGunCollider);


	(*autoGunCollider).InitSphereRadius(80.f);
	(*autoGunCollider).SetCollisionProfileName(TEXT("Trigger"));

}

void AAutomaticGunPickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;

	if (UWeaponComponent* weaponComponent = (*OtherActor).FindComponentByClass<UWeaponComponent>())
	{
		(*weaponComponent).EquipPickableWeapon(this);
		weaponComponent->defaultRifleWeapon->ImplementActiveState(false);
		currentAmmoAmount = 30;
 	}
}

void AAutomaticGunPickup::FireBullets()
{
	if (currentAmmoAmount <= 0)
	{
		return;		
    }
	if (currentAmmoAmount > 0)
	{
		Super::FireBullets();
	    currentAmmoAmount = currentAmmoAmount - 1;
	}
}

void AAutomaticGunPickup::BeginPlay()
{
	Super::BeginPlay();
	(*autoGunCollider).OnComponentBeginOverlap.AddDynamic(this, &AAutomaticGunPickup::OnPickupOverlap);
}

void AAutomaticGunPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

