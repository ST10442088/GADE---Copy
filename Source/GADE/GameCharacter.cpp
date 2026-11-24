// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Controller.h"
#include "InputAction.h"
#include "WeaponComponent.h"
#include "BaseWeaponClass.h"
#include "AmmoPickup.h"
#include "HealthComponent.h"


// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	cameraStick = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	cameraStick->SetupAttachment(RootComponent);
	cameraStick->TargetArmLength = 50.f;
	cameraStick->bUsePawnControlRotation = false;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(cameraStick, USpringArmComponent::SocketName);
	camera->bUsePawnControlRotation = false;

	auto characterMovementComp = GetCharacterMovement();
	characterMovementComp->bOrientRotationToMovement = true;
	characterMovementComp->bSnapToPlaneAtStart = true;
    
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;
	
	weaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Gun Component"));
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGameCharacter::Move(const FInputActionValue& Value)
{
	FVector2D inputValue = Value.Get<FVector2D>();
	if (Controller != nullptr && (inputValue.X != 0.0F || inputValue.Y != 0.0f))
	{
		const FRotator yaw_Z_rotation(0, Controller->GetControlRotation().Yaw, 0);
		if (inputValue.X != 0.0F)
		{
			FVector rightDirection = UKismetMathLibrary::GetRightVector(yaw_Z_rotation);
			AddMovementInput(rightDirection, inputValue.X);
		}

		if (inputValue.Y != 0.0f)
		{
			const FVector forwardDirection = yaw_Z_rotation.Vector();
			AddMovementInput(forwardDirection, inputValue.Y);
		}

	}
}

void AGameCharacter::LookAround(const FInputActionValue& Value)
{
	FVector2D inputValue = Value.Get<FVector2D>();
	if (inputValue.X != 0.0F)
	{
		AddControllerYawInput(inputValue.X);
	}

	if (inputValue.Y != 0.0F)
	{
		AddControllerPitchInput(inputValue.Y); 
	}
}

void AGameCharacter::StartSprinting()
{
	(*GetCharacterMovement()).MaxWalkSpeed = 900.f;

}

void AGameCharacter::StopSprinting()
{
	(*GetCharacterMovement()).MaxWalkSpeed = 500.f;
}



// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComponent != nullptr)
	{
		APlayerController* playerController = Cast<APlayerController>(GetController());
		if (playerController != nullptr)
		{
			UEnhancedInputLocalPlayerSubsystem* enhancedLocalSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
			if (enhancedLocalSystem != nullptr)
			{
				(*enhancedLocalSystem).AddMappingContext(IMC_Character, 1);
			}
		}
		(*enhancedInputComponent).BindAction(IA_Move, ETriggerEvent::Triggered, this, &AGameCharacter::Move);
		(*enhancedInputComponent).BindAction(IA_Jump, ETriggerEvent::Started, this, &AGameCharacter::Jump);
		(*enhancedInputComponent).BindAction(IA_Jump, ETriggerEvent::Completed, this, &AGameCharacter::StopJumping);
		(*enhancedInputComponent).BindAction(IA_Look, ETriggerEvent::Triggered, this, &AGameCharacter::LookAround);
		(*enhancedInputComponent).BindAction(IA_Shoot, ETriggerEvent::Triggered, this, &AGameCharacter::ShootBullets);
		(*enhancedInputComponent).BindAction(IA_SwitchToDefault, ETriggerEvent::Triggered, this, &AGameCharacter::SwitchToDefaultRifle);
		(*enhancedInputComponent).BindAction(IA_SwitchToAutoGun, ETriggerEvent::Triggered, this, &AGameCharacter::SwitchToAutoGun);
		(*enhancedInputComponent).BindAction(IA_Sprint, ETriggerEvent::Started, this, &AGameCharacter::StartSprinting);
		(*enhancedInputComponent).BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AGameCharacter::StopSprinting);

	}

}




void AGameCharacter::ShootBullets()
{
	if (weaponComponent != nullptr)
	{
		(*weaponComponent).FireBulletsWithEquippedWeapon();
	}
}

void AGameCharacter::SwitchToDefaultRifle()
{
	if (weaponComponent != nullptr)
	{
		(*weaponComponent).SwitchToDefaultRifle();
	}
}

void AGameCharacter::SwitchToAutoGun()
{
	if (weaponComponent != nullptr && (*weaponComponent).automaticPickupWeapon != nullptr)
	{
		(*weaponComponent).SwitchToAutoPickupGun();	
	}
}



