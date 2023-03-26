// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"

UStudent::UStudent()
{
	Name = TEXT("내잔학생");
	Card->SetCardType(ECardType::Student);
}

void UStudent::DoLesson()
{
	ILessonInterface::DoLesson();

	UE_LOG(LogTemp, Log, TEXT("%s은 수업을 듣습니다."), *Name);
}
