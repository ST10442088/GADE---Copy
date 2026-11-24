// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultRifle.h"
#include "Components/ArrowComponent.h"

void ADefaultRifle::FireBullets()
{
	Super::FireBullets();
	gunfireDamage = 3.f;
}

ADefaultRifle::ADefaultRifle()
{
	RootComponent = GunMesh;
	FRotator gunRotation(0, 0, 0);
	(*GunMesh).SetRelativeRotation(gunRotation);
}
