// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_MoveToCollectible.h"

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "MyBTTask_isPlayerDetected.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "MyPlayerCameraManager.h"

EBTNodeResult::Type UMyBTTask_MoveToCollectible::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        APawn* selfPawn = aiController->GetPawn();

        double startTime = FPlatformTime::Seconds();
        //auto measureAndLogTime = [&]()
        //    {
        //        double endTime = FPlatformTime::Seconds();
        //        double timeTakenInSeconds = endTime - startTime;
        //        double timeTakenInMilliseconds = timeTakenInSeconds * 1000.0;
        //        AMyPlayerCameraManager* UpdateManager = AMyPlayerCameraManager::GetInstance();
        //        if (UpdateManager)
        //        {
        //            UpdateManager->increment(timeTakenInSeconds);
        //        }
        //        FString debugMessage = FString::Printf(TEXT("Player detection time : %f ms"), timeTakenInMilliseconds);

        //        if (APawn* selfPawn = aiController->GetPawn())
        //        {
        //            FVector debugLocation = selfPawn->GetActorLocation() + FVector(20, 0, 100);
        //            // DrawDebugString(GetWorld(), debugLocation, debugMessage, nullptr, FColor::Yellow, DeltaSeconds, true);
        //        }
        //    };

        //if (!selfPawn)
        //{
        //    measureAndLogTime();
        //    return;
        //}

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


        if (aiController->currentCollectible == nullptr && BlackboardComp->GetValue<UBlackboardKeyType_Bool>(aiController->m_updateTick)) {
       
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Valeur : %f"), 0.002f));
            aiController->currentCollectible = aiController->GetRandomCollectible();
            aiController->MoveToLocation(aiController->currentCollectible->GetActorLocation(), 0.5f, false, true, false, false, NULL, false);
            pawn->SetActorTickEnabled(true);
            return EBTNodeResult::Succeeded;
           
        }

        pawn->SetActorTickEnabled(false);
       

    }
    return EBTNodeResult::Failed;
   
 
}