// Fill out your copyright notice in the Description page of Project Settings.
#include "MyBTTask_QuitFollowingGroup.h"

#include "MyBTTask_isPlayerDetected.h"
#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "FollowingGroupManager.h"

EBTNodeResult::Type UMyBTTask_QuitFollowingGroup::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
		FollowingGroupManager::RemoveFromGroup(aiController->GetPawn());
		return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}