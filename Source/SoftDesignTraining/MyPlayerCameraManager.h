// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "queueManager.h"
#include "MyPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API AMyPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:

    float TimeSpent;
    float AgentUpdateBudget;
    

    TArray<APawn*> ManagedAgents;

    // Constructeur
    AMyPlayerCameraManager();


    static AMyPlayerCameraManager* GetInstance();


    //void BeginPlay();


    void addAgent(APawn* Agent, float timedUsed);



    void removeAgent(APawn* Agent);

 

    TArray<APawn*> GetAllAgents() ;
	

    void resetAll();



    void increment(float timedUsed);
    void DebugPrint();
    //UPROPERTY()
    //TArray<ASDTAIController*> AgentsToUpdateNextFrame;

private:
    static AMyPlayerCameraManager* m_Instance;
    static void Destroy();


};
