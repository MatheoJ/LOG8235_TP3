// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_GoAround.h"

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "MyBTTask_isPlayerDetected.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "FollowingGroupManager.h"

EBTNodeResult::Type UMyBTTask_GoAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
        if ( BlackboardComp->GetValue<UBlackboardKeyType_Bool>(aiController->m_updateTick))
        {
        FVector objectif = FollowingGroupManager::lastKnownPosition;
		FVector random = FVector(FMath::RandRange(-15, 15), FMath::RandRange(-100, 100), 0);
		objectif += random;
        //aiController->MoveToLocation(objectif, 0.5f, false, true, false, false, NULL, false);

        OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(aiController->m_followingPosBBKeyID, objectif);
        
        return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}