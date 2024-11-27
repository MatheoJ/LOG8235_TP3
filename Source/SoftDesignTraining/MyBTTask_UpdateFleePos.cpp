// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_UpdateFleePos.h"

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "MyBTTask_isPlayerDetected.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

EBTNodeResult::Type UMyBTTask_UpdateFleePos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(aiController->m_fleePosBBKeyID, aiController->GetBestFleeLocation()->GetActorLocation());
		return EBTNodeResult::Succeeded;
    }

	return EBTNodeResult::Failed;    
}