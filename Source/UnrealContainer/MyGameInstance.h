// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

USTRUCT()
struct FStudentData
{
	GENERATED_BODY()

		FStudentData()
	{
		Name = TEXT("내잔");
		Order = -1;
	}

	FStudentData(FString InName, int32 InOrder) :
		Name(InName), Order(InOrder) {}

	//리플렉션이 필요한 변수는 프로퍼티 매크로 사용
	UPROPERTY()
		FString Name;

	UPROPERTY()
		int32 Order;

	//==연산자로 해시비교할때 사용합니다.
	bool operator==(const FStudentData& InOther) const
	{
		return Order == InOther.Order;
	}

	//해시 지정 함수
	friend FORCEINLINE uint32 GetTypeHash(const FStudentData& InStudentData)
	{
		return GetTypeHash(InStudentData.Order);
	}
};

/**
 *
 */
UCLASS()
class UNREALCONTAINER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

private:
	TArray<FStudentData> StudentsData;

	//TObjectPtr로 관리되는 객체는 반드시 UPROPERTY 매크로를 사용해줘야한다!
	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> Students;

	//TMap의 선언
	TMap<int32, FString> StudentsMap;
};
