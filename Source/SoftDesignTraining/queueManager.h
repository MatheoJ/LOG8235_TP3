// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "queueManager.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API UqueueManager : public UObject
{
	GENERATED_BODY()


public:

    TArray<APawn*> ManagedAgents;

    // Constructeur
    UqueueManager();



    void addAgent(APawn* Agent);





    void removeAgent(APawn* Agent);



    TArray<APawn*> GetAllAgents();

    static UqueueManager* GetInstance();


private:
    static UqueueManager* Instance;


	
};
