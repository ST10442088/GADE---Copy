// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckToDetectCharacter.h"
#include "BotAIController.h"
#include "BotCharacter.h"
#include "GameCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"



UBTService_CheckToDetectCharacter::UBTService_CheckToDetectCharacter()
{
	bNotifyTick = true;
}

void UBTService_CheckToDetectCharacter::TickNode(UBehaviorTreeComponent & OwnerComponent, uint8 * NodeMemory, float DeltaSeconds)
	{
		Super::TickNode(OwnerComponent, NodeMemory, DeltaSeconds);
	    blackboardComponent = OwnerComponent.GetBlackboardComponent();

	    const ABotAIController* aiController = Cast<ABotAIController>(OwnerComponent.GetAIOwner());
		if (aiController == nullptr) { UE_LOG(LogTemp, Warning, TEXT("No Controller")); return; }

	    APawn* aiControlledPawn = (*aiController).GetPawn();
	    if (aiControlledPawn == nullptr) { UE_LOG(LogTemp, Warning, TEXT("No pawn")); return; }

    	aiControlledCharacter = Cast<ABotCharacter>(aiControlledPawn);
    	if (aiControlledCharacter == nullptr) { UE_LOG(LogTemp, Warning, TEXT("No character")); return; }


		FVector sphereLocation = (*aiControlledCharacter).GetActorLocation();

		TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
		objectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

		TArray<AActor*> actorsToBeIgnored;
		actorsToBeIgnored.Add(aiControlledCharacter);

		TArray<AActor*> actorsOverlapped;
		UClass* classToFilterBy = ACharacter::StaticClass();

		bool enemyCharacterSphereDetector = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), sphereLocation, sphereRadius, objectTypes, classToFilterBy, actorsToBeIgnored, actorsOverlapped);
		DrawDebugSphere(GetWorld(), sphereLocation, sphereRadius, 24, FColor::Green, false, 1.f, 0, 2.5f);

		AActor* entityClosestToThisAI = nullptr;
		float closestDistanceToThisAI = MAX_FLT;

		if (enemyCharacterSphereDetector == true)
		{		UE_LOG(LogTemp, Warning, TEXT("Something"));
			for (AActor* overlappedActorsList : actorsOverlapped)
			{
				if (ACharacter* overlappedCharActor = Cast<ACharacter>(overlappedActorsList))
				{
		            UE_LOG(LogTemp, Warning, TEXT("Something 1"));
					float distance = FVector::DistSquared(sphereLocation, (*overlappedCharActor).GetActorLocation());
					if (closestDistanceToThisAI > distance)
					{
						closestDistanceToThisAI = distance;
						entityClosestToThisAI = overlappedCharActor;
					   
						FVector startPoint = (*aiControlledCharacter).GetActorLocation();
					    FVector endPoint = (*entityClosestToThisAI).GetActorLocation();

					    FRotator lookRotationDirection = UKismetMathLibrary::FindLookAtRotation(startPoint, endPoint);
				    	(*aiControlledCharacter).SetActorRotation(lookRotationDirection);
					}
				}
			}
		}

		(*blackboardComponent).SetValueAsObject(IsCharacterDetected.SelectedKeyName, entityClosestToThisAI);
	}
