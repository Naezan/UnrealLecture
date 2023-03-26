// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameUI.generated.h"

/**
 *
 */
UCLASS()
class UNREALDELEGATE_API UGameUI : public UObject
{
	GENERATED_BODY()

public:
	UGameUI();

	void PrintGameUI(int InGameScore, int InPlayerCount);
};
