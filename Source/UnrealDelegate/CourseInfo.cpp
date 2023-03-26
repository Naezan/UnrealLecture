// Fill out your copyright notice in the Description page of Project Settings.


#include "CourseInfo.h"

UCourseInfo::UCourseInfo()
{
	Contents = TEXT("기존 학사 정보");
}

void UCourseInfo::ChangeCourceInfo(const FString& InSchoolName, const FString& InNewContents)
{
	Contents = InNewContents;

	UE_LOG(LogTemp, Log, TEXT("[CourceInfo] 학사 정보가 변경되어 알림을 발송합니다."));
	OnCourceInfoChanged.Broadcast(InSchoolName, Contents);
}
