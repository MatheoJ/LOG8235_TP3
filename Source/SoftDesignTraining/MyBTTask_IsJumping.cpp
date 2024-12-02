#include "MyBTTask_IsJumping.h"
#include "SDTAIController.h"
#include <BehaviorTree/Blackboard/BlackboardKeyType_Bool.h>

EBTNodeResult::Type UMyBTTask_IsJumping::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (!aiController)
    {
        UE_LOG(LogTemp, Error, TEXT("AIController is null in UMyBTTask_IsJumping::ExecuteTask"));
        return EBTNodeResult::Failed;
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

    if (!BlackboardComp->GetValue<UBlackboardKeyType_Bool>(aiController->m_updateTick)) {
        pawn->SetActorTickEnabled(false);
        return EBTNodeResult::Failed;
    }

    pawn->SetActorTickEnabled(true);

	if (aiController->AtJumpSegment)
	{
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}