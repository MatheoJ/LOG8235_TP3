// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_GoAround.h"

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "MyBTTask_isPlayerDetected.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
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

        if (!BlackboardComp->GetValue<UBlackboardKeyType_Bool>(aiController->m_updateTick))
        {
			return EBTNodeResult::Failed;
		}

        FVector objectif = FollowingGroupManager::lastKnownPosition;

        FVector CurrentAIm = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(aiController->m_followingPosBBKeyID);

        float currentDistance = FVector::Distance(CurrentAIm, objectif);

		float angle = BlackboardComp->GetValue<UBlackboardKeyType_Float>(aiController->m_angle);
        FVector random = FVector(LookAroundDistance * FMath::Cos(angle), LookAroundDistance * FMath::Sin(angle), 0);
        objectif += random;

        DrawDebugSphere(GetWorld(), objectif, 50.f, 8, FColor::Orange);

        OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(aiController->m_followingPosBBKeyID, objectif);

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}