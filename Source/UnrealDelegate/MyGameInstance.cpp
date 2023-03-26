// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "CourseInfo.h"
#include "GameData.h"
#include "GameUI.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	//학사정보와 학생
	{
		CourceInfo = NewObject<UCourseInfo>(this);

		UStudent* Student1 = NewObject<UStudent>();
		Student1->SetName(TEXT("학생1"));
		UStudent* Student2 = NewObject<UStudent>();
		Student2->SetName(TEXT("학생2"));
		UStudent* Student3 = NewObject<UStudent>();
		Student3->SetName(TEXT("학생3"));

		CourceInfo->OnCourceInfoChanged.AddUObject(Student1, &UStudent::GetNotification);
		CourceInfo->OnCourceInfoChanged.AddUObject(Student2, &UStudent::GetNotification);
		CourceInfo->OnCourceInfoChanged.AddUObject(Student3, &UStudent::GetNotification);

		CourceInfo->ChangeCourceInfo(SchoolName, TEXT("변경된 학사정보"));
	}
	
	//게임데이터 매니저와 게임UI
	UGameData* MyGameData = NewObject<UGameData>();
	UGameUI* MyGameUI = NewObject<UGameUI>();

	MyGameData->OnGameDataChanged.BindUObject(MyGameUI, &UGameUI::PrintGameUI);

	MyGameData->SetGameScore(100);
	MyGameData->SetPlayerCount(4);
}
