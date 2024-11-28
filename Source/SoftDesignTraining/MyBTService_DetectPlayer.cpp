// Fill out your copyright notice in the Description page of Project Settings.
#include "MyBTService_DetectPlayer.h"

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"


#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include <AIController.h>

#include "FollowingGroupManager.h"



UMyBTService_DetectPlayer::UMyBTService_DetectPlayer()
{
}

void UMyBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
         
        bool playerSeen = aiController->hasPlayerInLoS();
        if (playerSeen)
        {
            //write to bb that the player is seen
            OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->m_playerDetectedBBKeyID, true);

            ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

            //write to bb the position of the target
            OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(aiController->m_playerPosBBKeyID, playerCharacter->GetActorLocation());
        }
        else
        {
            //write to bb that the player is not seen
            OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->m_playerDetectedBBKeyID, false);
        }        
    }
}
