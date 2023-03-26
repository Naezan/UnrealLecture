// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData.h"

UGameData::UGameData()
{
}

void UGameData::SetGameScore(int InScore)
{
	GameScore = InScore;
	OnGameDataChanged.Execute(GameScore, PlayerCount);
}

void UGameData::SetPlayerCount(int InCount)
{
	PlayerCount = InCount;
	OnGameDataChanged.Execute(GameScore, PlayerCount);
}
