// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SOFTDESIGNTRAINING_API FollowingGroupManager
{
public:
	FollowingGroupManager();
	~FollowingGroupManager();

	static void AddToGroup(APawn* character);
	static void RemoveFromGroup(APawn* character);
	static bool isInGroup(APawn* character);

	static inline FVector lastKnownPosition{ FVector::Zero() };

private: 	
	static inline TArray<APawn*> m_followingGroup{};
};
