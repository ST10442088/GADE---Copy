// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "BaseWeaponClass.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ownerOfThisWeaponComponent = Cast<ACharacter>(GetOwner());
	UWorld* gameWorld = GetWorld();
	if (defaultWeapon_To_BeAssignedInBP != nullptr && gameWorld != nullptr)
	{
		FActorSpawnParameters gunSpawnParameters;
		gunSpawnParameters.Owner = GetOwner();
		gunSpawnParameters.Instigator = ownerOfThisWeaponComponent;

		defaultRifleWeapon = (*GetWorld()).SpawnActor<ABaseWeaponClass>(defaultWeapon_To_BeAssignedInBP, gunSpawnParameters);
		if (defaultRifleWeapon != nullptr)
		{
			(*defaultRifleWeapon).SetActorEnableCollision(false);
			AttachWeaponToCharacter(defaultRifleWeapon);
			currentlyEquippedWeapon = defaultRifleWeapon;
		}
	}
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UWeaponComponent::EquipPickableWeapon(ABaseWeaponClass* weaponPickup)
{
	if (weaponPickup == nullptr)
	{
		return;
	}

	if (automaticPickupWeapon != nullptr)
	{
		(*weaponPickup).Destroy();
		return;
	}

	automaticPickupWeapon = weaponPickup;
	(*automaticPickupWeapon).SetOwner(GetOwner());
	(*automaticPickupWeapon).SetInstigator(ownerOfThisWeaponComponent);

	if (UPrimitiveComponent* sphereCollider = (*automaticPickupWeapon).FindComponentByClass<USphereComponent>())
	{
		(*sphereCollider).SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}

	AttachWeaponToCharacter(automaticPickupWeapon);
	SwitchToAutoPickupGun();

}




void UWeaponComponent::AttachWeaponToCharacter(ABaseWeaponClass* weaponToBeAttached)
{

	if (weaponToBeAttached == automaticPickupWeapon)
	{
	    (*weaponToBeAttached).AttachToComponent((*ownerOfThisWeaponComponent).GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("AutoGunSocket")));
		(*weaponToBeAttached).SetOwner(ownerOfThisWeaponComponent);
		(*weaponToBeAttached).SetInstigator(ownerOfThisWeaponComponent);

	}

	else if (weaponToBeAttached == defaultRifleWeapon)
	{
		(*weaponToBeAttached).AttachToComponent((*ownerOfThisWeaponComponent).GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName(TEXT("DefaultRifleSocket")));
		(*weaponToBeAttached).SetOwner(ownerOfThisWeaponComponent);
		(*weaponToBeAttached).SetInstigator(ownerOfThisWeaponComponent);
	}
}




void UWeaponComponent::SwitchToDefaultRifle()
{
	if (defaultRifleWeapon == nullptr || currentlyEquippedWeapon == defaultRifleWeapon) return;
	if (currentlyEquippedWeapon == automaticPickupWeapon)
	{
		(*currentlyEquippedWeapon).ImplementActiveState(false);
	}
	currentlyEquippedWeapon = defaultRifleWeapon;
	(*currentlyEquippedWeapon).ImplementActiveState(true);
}




void UWeaponComponent::SwitchToAutoPickupGun()
{
	if (automaticPickupWeapon == nullptr || currentlyEquippedWeapon == automaticPickupWeapon) return;
	if (currentlyEquippedWeapon == defaultRifleWeapon)
	{
		(*currentlyEquippedWeapon).ImplementActiveState(false);
	}

	currentlyEquippedWeapon = automaticPickupWeapon;
	(*currentlyEquippedWeapon).ImplementActiveState(true);
}

bool UWeaponComponent::RefillAmmo()
{
	if (currentlyEquippedWeapon != nullptr )
	{
		if (automaticPickupWeapon != nullptr)
		{
			(*automaticPickupWeapon).currentAmmoAmount = 30;
			(*automaticPickupWeapon).OnNewAmmoAmount.Broadcast((*automaticPickupWeapon).currentAmmoAmount);
		    return true;
		}
    }
	return false;
}




void UWeaponComponent::FireBulletsWithEquippedWeapon()
{
	if (currentlyEquippedWeapon != nullptr)
	{
		(*currentlyEquippedWeapon).FireBullets();
	}
}

int32 UWeaponComponent::GetCurrentAmmoAmount()
{
	if (automaticPickupWeapon != nullptr)
	{
		return automaticPickupWeapon->currentAmmoAmount;
	}
	return 0;
}





