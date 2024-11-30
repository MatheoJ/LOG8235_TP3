// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCameraManager.h"
#include <Kismet/GameplayStatics.h>

AMyPlayerCameraManager* AMyPlayerCameraManager::m_Instance = nullptr;

AMyPlayerCameraManager::AMyPlayerCameraManager()
{
    PrimaryActorTick.bCanEverTick = true; 
    TimeSpent = 0.0f; 
    AgentUpdateBudget = 0.002f;

}

AMyPlayerCameraManager* AMyPlayerCameraManager::GetInstance()
{
    if (!m_Instance)
    {
        m_Instance = NewObject<AMyPlayerCameraManager>();
        m_Instance->AddToRoot();
        if (GEngine && GEngine->GetWorld())
        {

            GEngine->GetWorld()->SpawnActor<AMyPlayerCameraManager>(AMyPlayerCameraManager::StaticClass());
        }
    }
    return m_Instance;
}


//void AMyPlayerCameraManager::BeginPlay()
//{
//    Super::BeginPlay(); 
//    TimeSpent = 0.0f;
//
//  
//
//}


void AMyPlayerCameraManager::Destroy()
{
    if (m_Instance)
    {
        m_Instance->resetAll();
        m_Instance->RemoveFromRoot();
        m_Instance = nullptr;
      // m_Instance->TimeSpent = 0.0f;
    }
}


void AMyPlayerCameraManager::addAgent(APawn* Agent, float timedUsed)
{
    
    if (!Agent)
    {

        return;
    }


    UqueueManager* queueManager = UqueueManager::GetInstance();
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Valeur : %d"), queueManager->GetAllAgents().Num()));
   // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Valeur : %d"), TimeSpent));
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Valeur : %d"), queueManager->GetAllAgents().Num()));

    if (!queueManager)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize queueManager in AMyPlayerCameraManager::BeginPlay"));
        return;
    }



   

    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Valeur : %f"), TimeSpent));
    if (queueManager->GetAllAgents().Contains(Agent) && TimeSpent < AgentUpdateBudget && !ManagedAgents.Contains(Agent))
    {

        increment(timedUsed);
        queueManager->removeAgent(Agent);
        ManagedAgents.Add(Agent);
         GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("queue : %f"), TimeSpent));
    }


    else if (queueManager->GetAllAgents().IsEmpty() && TimeSpent < AgentUpdateBudget && !ManagedAgents.Contains(Agent))
    {
        
        increment(timedUsed);
        ManagedAgents.Add(Agent);
         GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("de base : %f"), TimeSpent));
    }

    else
    {
          GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Valeur : %f"), TimeSpent));
        queueManager->addAgent(Agent);
    }

    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::  Green, FString::Printf(TEXT("ti;e : %d"), TimeSpent));
    
}


void AMyPlayerCameraManager::removeAgent(APawn* Agent)
{
    if (Agent)
    {
        ManagedAgents.Remove(Agent);
    }
}


TArray<APawn*> AMyPlayerCameraManager::GetAllAgents() 
{
    return ManagedAgents;
}

void AMyPlayerCameraManager::increment(float timedUsed)
{
     TimeSpent += timedUsed;
    
     //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Valeur : %f"), 0.002f));
     //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Valeur : %d"),TimeSpent ));
}

void AMyPlayerCameraManager::resetAll()
{
    TimeSpent = 0.0f;
    ManagedAgents.Reset();

}


//void AMyPlayerCameraManager::DebugPrint() 
//{
//    FString QueueContents;
//    for (ASDTAIController* Controller : AgentsToUpdateNextFrame)
//    {
//        if (Controller)
//        {
//            QueueContents += Controller->GetName() + TEXT(", ");
//        }
//    }
//
//    if (QueueContents.IsEmpty())
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Queue is empty"));
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Agents in queue: %s"), *QueueContents);
//    }
//}
