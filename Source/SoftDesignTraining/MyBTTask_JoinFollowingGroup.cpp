// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_JoinFollowingGroup.h"

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "MyBTTask_isPlayerDetected.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "FollowingGroupManager.h"

EBTNodeResult::Type UMyBTTask_JoinFollowingGroup::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
		FollowingGroupManager::AddToGroup(aiController->GetPawn());
		FollowingGroupManager::lastKnownPosition = 
            OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(aiController->m_playerPosBBKeyID);

		return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}