// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponClass.h"
#include "AutomaticGunPickup.generated.h"



/**
 * 
 */
UCLASS()
class GADE_API AAutomaticGunPickup : public ABaseWeaponClass
{
	GENERATED_BODY()
public:
	AAutomaticGunPickup();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* autoGunCollider;

	UFUNCTION()
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void FireBullets() override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AAutomaticGunPickup> autoGun;

	UFUNCTION(BlueprintPure)
	int32 GetCurrentAmmo() { return currentAmmoAmount; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
