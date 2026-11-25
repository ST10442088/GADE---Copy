// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckAmmo.h"
#include "BotAIController.h"
#include "BotCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "WeaponComponent.h"
#include "BaseWeaponClass.h"

UBTService_CheckAmmo::UBTService_CheckAmmo()
{
	bCreateNodeInstance = true;
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
	bNotifyTick = false;
}

void UBTService_CheckAmmo::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComponent, NodeMemory);
	 blackboardComponent = OwnerComponent.GetBlackboardComponent();

	const ABotAIController* aiController = Cast<ABotAIController>(OwnerComponent.GetAIOwner());
	if (aiController == nullptr) { return; }

	APawn* aiControlledPawn = (*aiController).GetPawn();
	if (aiControlledPawn == nullptr) { return; }

    aiControlledCharacter = Cast<ABotCharacter>(aiControlledPawn);
	if (aiControlledCharacter == nullptr) { return; }

	if (aiControlledCharacter->weaponComponent->currentlyEquippedWeapon != nullptr)
	{
		aiControlledCharacter->weaponComponent->currentlyEquippedWeapon->OnNewAmmoAmount.AddDynamic(this, &UBTService_CheckAmmo::OnAmmoChanged);
	}
}

void UBTService_CheckAmmo::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComponent, NodeMemory);
	if (aiControlledCharacter->weaponComponent->currentlyEquippedWeapon != nullptr)
	{
		aiControlledCharacter->weaponComponent->currentlyEquippedWeapon->OnNewAmmoAmount.RemoveDynamic(this, &UBTService_CheckAmmo::OnAmmoChanged);
	}
}

void UBTService_CheckAmmo::OnAmmoChanged(int32 ammoAmount)
{
	if (ammoAmount < 15)
	{
		(*blackboardComponent).SetValueAsBool(IsAmmoBelowHalf.SelectedKeyName, true);
	}
}
