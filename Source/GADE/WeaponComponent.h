// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseWeaponClass;
class AGameCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GADE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void EquipPickableWeapon(ABaseWeaponClass* weaponPickup);

	void AttachWeaponToCharacter(ABaseWeaponClass* weaponToBeAttached);

	void SwitchToDefaultRifle();
	void SwitchToAutoPickupGun();
	bool RefillAmmo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ABaseWeaponClass* defaultRifleWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ABaseWeaponClass* automaticPickupWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ABaseWeaponClass* currentlyEquippedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseWeaponClass> defaultWeapon_To_BeAssignedInBP;

	void FireBulletsWithEquippedWeapon();

	class ACharacter* ownerOfThisWeaponComponent;

	

	UFUNCTION(BlueprintPure)
	int32 GetCurrentAmmoAmount();


};
