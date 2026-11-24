// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponClass.h"
#include "DefaultRifle.generated.h"

/**
 * 
 */
UCLASS()
class GADE_API ADefaultRifle : public ABaseWeaponClass
{
	GENERATED_BODY()
public:
	virtual void FireBullets() override;
	ADefaultRifle();
};
