// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HealthComponent.h"
#include "GameCharacter.h"
#include "BotCharacter.h"
#include "WeaponComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bulletProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Comp"));
	(*bulletProjectileComp).InitialSpeed = 1500.f;
	(*bulletProjectileComp).ProjectileGravityScale = 0.0f;

	bulletCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Bullet Collision"));
	(*bulletCollider).SetSphereRadius(30.f);
	(*bulletCollider).SetCollisionProfileName(FName("Bullets"));
	(*bulletCollider).SetSimulatePhysics(true);
	RootComponent = bulletCollider;

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	(*bulletMesh).SetupAttachment(bulletCollider);

	(*bulletCollider).OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5);
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != nullptr && OtherActor != this && OtherActor != GetInstigator())
	{
		UGameplayStatics::ApplyDamage(OtherActor, 12, GetInstigatorController(), this, UDamageType::StaticClass());
    	Destroy();
	}

}



