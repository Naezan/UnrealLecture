// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUI.h"

UGameUI::UGameUI()
{
}

void UGameUI::PrintGameUI(int InGameScore, int InPlayerCount)
{
	UE_LOG(LogTemp, Log, TEXT("현재 게임 점수는 : %d 현재 플레이어 수 : %d"), InGameScore, InPlayerCount);
}
