// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "StudentManager.h"

void CheckUObjectIsValid(const UObject* InObject, const FString& InTag)
{
	if (InObject->IsValidLowLevel())//IsValid보다 좀 더 정교하게 체크주는 함수
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효한 언리얼 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효하지 않은 언리얼 오브젝트"), *InTag);
	}
}

void CheckUObjectIsNull(const UObject* InObject, const FString& InTag)
{
	if (InObject == nullptr)//IsValid보다 좀 더 정교하게 체크주는 함수
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 널포인터 언리얼 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 낫널포인터 언리얼 오브젝트"), *InTag);
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	NonPropStudent = NewObject<UStudent>();
	PropStudent = NewObject<UStudent>();

	NonPropStudents.Add(NewObject<UStudent>());
	PropStudents.Add(NewObject<UStudent>());

	StudentManager = new FStudentManager(NewObject<UStudent>());
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	const UStudent* StudentInManager = StudentManager->GetStudent();

	delete StudentManager;
	StudentManager = nullptr;

	CheckUObjectIsNull(StudentInManager, TEXT("StudentInManager"));
	CheckUObjectIsValid(StudentInManager, TEXT("StudentInManager"));

	CheckUObjectIsNull(NonPropStudent, TEXT("NonPropStudent"));
	CheckUObjectIsValid(NonPropStudent, TEXT("NonPropStudent"));

	CheckUObjectIsNull(PropStudent, TEXT("PropStudent"));
	CheckUObjectIsValid(PropStudent, TEXT("PropStudent"));

	CheckUObjectIsNull(NonPropStudents[0], TEXT("NonPropStudents"));
	CheckUObjectIsValid(NonPropStudents[0], TEXT("NonPropStudents"));

	CheckUObjectIsNull(PropStudents[0], TEXT("PropStudents"));
	CheckUObjectIsValid(PropStudents[0], TEXT("PropStudents"));
}
