// Fill out your copyright notice in the Description page of Project Settings.


#include "queueManager.h"
#include <EngineMinimal.h>

UqueueManager* UqueueManager::Instance = nullptr;

UqueueManager::UqueueManager() {}

void UqueueManager::addAgent(APawn* Agent)
{
    if (Agent && !ManagedAgents.Contains(Agent))
    {
        ManagedAgents.Add(Agent);
    }
}

void UqueueManager::removeAgent(APawn* Agent)
{
    if (Agent)
    {
        ManagedAgents.Remove(Agent);
    }
}

TArray<APawn*> UqueueManager::GetAllAgents()
{
    return ManagedAgents;
}

UqueueManager* UqueueManager::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UqueueManager>();
        Instance->AddToRoot();
        if (GEngine && GEngine->GetWorld())
        {
            GEngine->GetWorld()->SpawnActor<UqueueManager>(UqueueManager::StaticClass());
        }
    }
    return Instance;
}
