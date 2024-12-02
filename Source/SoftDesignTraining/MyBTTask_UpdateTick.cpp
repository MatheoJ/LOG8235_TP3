// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_UpdateTick.h"
#include "SDTAIController.h"
#include <BehaviorTree/Blackboard/BlackboardKeyType_Bool.h>

EBTNodeResult::Type UMyBTTask_UpdateTick::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (!aiController)
    {
        UE_LOG(LogTemp, Error, TEXT("AIController is null in UMyBTTask_UpdateTick::ExecuteTask"));
        return EBTNodeResult::Failed; // Retournez "Failed" si le contrôleur est nul
    }
   
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
   
    if (BlackboardComp->GetValue<UBlackboardKeyType_Bool>(aiController->m_updateTick))
    {
        pawn->SetActorTickEnabled(true); 

        return EBTNodeResult::Succeeded; 
    }

    pawn->SetActorTickEnabled(false);
    return EBTNodeResult::Failed; 
}
