// Fill out your copyright notice in the Description page of Project Settings.


#include "Teacher.h"
#include "Card.h"

UTeacher::UTeacher()
{
	Name = TEXT("내잔선생");
	Card->SetCardType(ECardType::Teacher);
}

void UTeacher::DoLesson()
{
	ILessonInterface::DoLesson();

	UE_LOG(LogTemp, Log, TEXT("%s님은 수업을 합니다."), *Name);
}
