// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_TickUpdate.h"
#include "SDTAIController.h"
#include <BehaviorTree/Blackboard/BlackboardKeyType_Bool.h>
#include "MyPlayerCameraManager.h"
#include <EngineMinimal.h>

UMyBTService_TickUpdate::UMyBTService_TickUpdate()
{
    CurrentAgentIndex = 0;
     StartTime = FPlatformTime::Seconds();
}

void UMyBTService_TickUpdate::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        APawn* pawn = aiController->GetPawn();
        UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
        if (!BlackboardComp || !pawn)
        {
            UE_LOG(LogTemp, Error, TEXT("BlackboardComponent or Pawn is null in UMyBTService_TickUpdate::TickNode"));
            return;
        }

        AMyPlayerCameraManager* UpdateManager = AMyPlayerCameraManager::GetInstance();
        if (!UpdateManager)
        {
            UE_LOG(LogTemp, Error, TEXT("UpdateManager is null"));
            return;
        }
        
        const double Budget = 0.002f;

        UWorld* World = GetWorld();
        if (!World)
        {
            UE_LOG(LogTemp, Error, TEXT("World is null in TickNode"));
            return;
        }

        double CurrentTime = FPlatformTime::Seconds();
        if (CurrentTime - StartTime >= Budget)
        {
            StartTime = FPlatformTime::Seconds();
            BlackboardComp->SetValue<UBlackboardKeyType_Bool>(aiController->m_updateTick, false);
        }
            
        if (DeltaSeconds>= 0.599f)
        {
            UpdateManager->resetAll();
        }

        if (aiController->IsAgentVisibleInCamera(pawn))
        {
            UpdateManager->addAgent(pawn, (CurrentTime - StartTime));
        }

        if (UpdateManager->GetAllAgents().Contains(pawn) || UpdateManager->GetAllAgents().Num() == 0) {
            BlackboardComp->SetValue<UBlackboardKeyType_Bool>(aiController->m_updateTick, true);
        }
        else
        {
            BlackboardComp->SetValue<UBlackboardKeyType_Bool>(aiController->m_updateTick, false);
        }
    }


}