// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_MoveTowards.h"

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "MyBTTask_isPlayerDetected.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "FollowingGroupManager.h"

EBTNodeResult::Type UMyBTTask_MoveTowards::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        aiController->MoveToLocation(aiController->currentCollectible->GetActorLocation(), 0.5f, false, true, false, false, NULL, false);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
