// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "CustomGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (GetOwner() != nullptr)
	{
		(*GetOwner()).OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DrainHealth);
	}

}

void UHealthComponent::DrainHealth(AActor* damagedActor, float healthAmountLost, const UDamageType* damageType, AController* InstigatedBy, AActor* damageBringer)
{
	if (GetOwner() == nullptr) return;
	if (GetOwner() != nullptr)
	{
	
		Health = Health - healthAmountLost;
		HealthAmountChange.Broadcast(Health);
	
		if (Health <= 0)
		{
			Health = 0;

			AActor* ownerOfThisComponent = GetOwner();
		
			AController* characterController = Cast<AController>((*ownerOfThisComponent).GetInstigatorController());
		
			if (characterController == nullptr)
			{
				if (APawn* pawnOwning = Cast<APawn>(ownerOfThisComponent))
				{	
					characterController = (*pawnOwning).GetController();
				}
			}

		
			if (characterController != nullptr)	
			{
				APawn* instigatingPawn = nullptr;

				if ( damageBringer != nullptr)	
				{  
					instigatingPawn = (*damageBringer).GetInstigator();  	
				}
			
				if (instigatingPawn == nullptr)
				{
				   UE_LOG(LogTemp, Warning, TEXT("Instigating pawn not available"));
				}

				if (instigatingPawn != nullptr)	
				{
					UE_LOG(LogTemp, Warning, TEXT("Instigating pawn available"));
					for (const FName& possibleTag : desiredTags)
					{
						if ((*instigatingPawn).ActorHasTag(possibleTag) == true)
						{
					        UE_LOG(LogTemp, Warning, TEXT("Has tag available"));
							ACustomGameMode* gameMode = Cast<ACustomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
				
							if (gameMode != nullptr)		
							{
								(*gameMode).IncreaseKillCount(possibleTag);
								(*gameMode).RespawnCharacter(characterController);
							}
						}	
					}
				}
			}

			(*ownerOfThisComponent).Destroy();
		}
	}

}

