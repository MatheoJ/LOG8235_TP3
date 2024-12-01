// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_isCloseEnough.h"

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "MyBTTask_isPlayerDetected.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "FollowingGroupManager.h"

EBTNodeResult::Type UMyBTTask_isCloseEnough::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        constexpr float distanceThreshold = 30.0f;
        if (FVector::Dist(aiController->GetPawn()->GetActorLocation(), FollowingGroupManager::lastKnownPosition) < distanceThreshold) {
            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Failed;
}