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
		Name = TEXT("����");
		Order = -1;
	}

	FStudentData(FString InName, int32 InOrder) :
		Name(InName), Order(InOrder) {}

	//���÷����� �ʿ��� ������ ������Ƽ ��ũ�� ���
	UPROPERTY()
		FString Name;

	UPROPERTY()
		int32 Order;

	//==�����ڷ� �ؽú��Ҷ� ����մϴ�.
	bool operator==(const FStudentData& InOther) const
	{
		return Order == InOther.Order;
	}

	//�ؽ� ���� �Լ�
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

	//TObjectPtr�� �����Ǵ� ��ü�� �ݵ�� UPROPERTY ��ũ�θ� ���������Ѵ�!
	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> Students;

	//TMap�� ����
	TMap<int32, FString> StudentsMap;
};
