// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowingGroupManager.h"

FollowingGroupManager::FollowingGroupManager()
{

}

FollowingGroupManager::~FollowingGroupManager()
{
}

void FollowingGroupManager::AddToGroup(APawn* character)
{
	if (isInGroup(character))
	{
		return;
	}
	m_followingGroup.Add(character);
}

void FollowingGroupManager::RemoveFromGroup(APawn* character)
{
	if (!isInGroup(character))
	{
		return;
	}
	m_followingGroup.Remove(character);

	if (m_followingGroup.Num() == 0) {
		lastKnownPosition = FVector::Zero();
	}
}

bool FollowingGroupManager::isInGroup(APawn* character)
{
	return m_followingGroup.Contains(character);
}
