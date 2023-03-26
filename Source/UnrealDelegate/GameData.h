// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameData.generated.h"

DECLARE_DELEGATE_TwoParams(FOnGameDataChangedDelegate, int, int);

/**
 *
 */
UCLASS()
class UNREALDELEGATE_API UGameData : public UObject
{
	GENERATED_BODY()

public:
	UGameData();

	FOnGameDataChangedDelegate OnGameDataChanged;

	void SetGameScore(int InScore);
	void SetPlayerCount(int InCount);

private:
	int GameScore;
	int PlayerCount;
};
