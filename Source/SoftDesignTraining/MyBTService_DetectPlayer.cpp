// Fill out your copyright notice in the Description page of Project Settings.
#include "MyBTService_DetectPlayer.h"

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"


#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"



UMyBTService_DetectPlayer::UMyBTService_DetectPlayer()
{
}

void UMyBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    //if (ASoftDesignAIController* aiController = Cast<ASoftDesignAIController>(OwnerComp.GetAIOwner()))
    //{
    //    //Trigger from service the detect
    //    if (AAIBase* aiBase = Cast<AAIBase>(aiController->GetCharacter()))
    //    {
    //        aiBase->DetectPlayer();
    //        if (aiBase->IsTargetPlayerSeen())
    //        {
    //            //write to bb that the player is seen
    //            OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetTargetSeenKeyID(), true);

    //            //write to bb the position of the target
    //            OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(aiController->GetTargetPosBBKeyID(), aiBase->GetTargetPlayerPos());
    //        }
    //        else
    //        {
    //            //write to bb that the player is not seen
    //            OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetTargetSeenKeyID(), false);
    //        }

    //    }
    //}
}