// Fill out your copyright notice in the Description page of Project Settings.
#include "MyBTTask_isPlayerDetected.h"
#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "FollowingGroupManager.h"
#include "MyPlayerCameraManager.h"

EBTNodeResult::Type UMyBTTask_isPlayerDetected::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

        if (OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Bool>(aiController->m_playerDetectedBBKeyID)) {
            pawn->SetActorTickEnabled(true);
            return EBTNodeResult::Succeeded;
        }
        pawn->SetActorTickEnabled(false);
    }

    return EBTNodeResult::Failed;
}