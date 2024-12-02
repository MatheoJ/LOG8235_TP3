// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_JoinFollowingGroup.h"

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "MyBTTask_isPlayerDetected.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "FollowingGroupManager.h"

EBTNodeResult::Type UMyBTTask_JoinFollowingGroup::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        APawn* pawn = aiController->GetPawn();
        if (!pawn)
        {
            UE_LOG(LogTemp, Error, TEXT("Pawn is null in UMyBTTask_UpdateTick::ExecuteTask"));
            return EBTNodeResult::Failed; // Retournez "Failed" si le Pawn est nul
        }

        UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
        if (!BlackboardComp)
        {
            UE_LOG(LogTemp, Error, TEXT("BlackboardComponent is null in UMyBTTask_UpdateTick::ExecuteTask"));
            return EBTNodeResult::Failed;
        }

        if (!BlackboardComp->GetValue<UBlackboardKeyType_Bool>(aiController->m_updateTick)) {
            pawn->SetActorTickEnabled(false);
            return EBTNodeResult::Failed;
        }

        pawn->SetActorTickEnabled(true);
		BlackboardComp->SetValue<UBlackboardKeyType_Float>(aiController->m_angle, FMath::RandRange(0, 360));
		FollowingGroupManager::AddToGroup(pawn);
		FollowingGroupManager::lastKnownPosition = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(aiController->m_playerPosBBKeyID);
		return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}