// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_MonitorHealthAmount.h"
#include "BotAIController.h"
#include "BotCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HealthComponent.h"

UBTService_MonitorHealthAmount::UBTService_MonitorHealthAmount()
{
	bCreateNodeInstance = true;
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
	bNotifyTick = false;
}


void UBTService_MonitorHealthAmount::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComponent, NodeMemory);
	blackboardComponent = OwnerComponent.GetBlackboardComponent();

	const ABotAIController* aiController = Cast<ABotAIController>(OwnerComponent.GetAIOwner());
	if (aiController == nullptr) { return; }

	APawn* aiControlledPawn = (*aiController).GetPawn();
	if (aiControlledPawn == nullptr) { return; }

	aiControlledCharacter = Cast<ABotCharacter>(aiControlledPawn);
	if (aiControlledCharacter == nullptr) { return; }
	aiControlledCharacter->healthComponent->HealthAmountChange.AddDynamic(this, &UBTService_MonitorHealthAmount::OnHealthChange);
}

void UBTService_MonitorHealthAmount::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComponent, NodeMemory);
	aiControlledCharacter->healthComponent->HealthAmountChange.RemoveDynamic(this, &UBTService_MonitorHealthAmount::OnHealthChange);
}

void UBTService_MonitorHealthAmount::OnHealthChange(int32 healthAmount)
{
	if (healthAmount < 25)
	{
		(*blackboardComponent).SetValueAsBool(IsHealthTooLow.SelectedKeyName, true);
	}
}
