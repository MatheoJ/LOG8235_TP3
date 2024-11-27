// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_MoveToCollectible.h"

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "MyBTTask_isPlayerDetected.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

EBTNodeResult::Type UMyBTTask_MoveToCollectible::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {

        if (aiController->currentCollectible == nullptr)
        {
            aiController->currentCollectible = aiController->GetRandomCollectible();
            aiController->MoveToLocation(aiController->currentCollectible->GetActorLocation(), 0.5f, false, true, false, false, NULL, false);
        }
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}