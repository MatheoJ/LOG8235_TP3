// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTService_TickUpdate.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API UMyBTService_TickUpdate : public UBTService
{
	GENERATED_BODY()

public:
	UMyBTService_TickUpdate();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	int CurrentAgentIndex;
	double StartTime;
	
};
