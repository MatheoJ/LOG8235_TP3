// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_isPlayerPoweredUp.h"
#include "SDTUtils.h"

EBTNodeResult::Type UMyBTTask_isPlayerPoweredUp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (SDTUtils::IsPlayerPoweredUp(GetWorld())) 
    {
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}