// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Algo/Accumulate.h"

//랜덤 이름 만들기
FString MakeRandomName()
{
	TCHAR FirstChar[] = TEXT("김이박최");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[] = TEXT("수은원연");

	TArray<TCHAR> RandomArray;
	RandomArray.SetNum(3);
	RandomArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandomArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandomArray[2] = LastChar[FMath::RandRange(0, 3)];

	return RandomArray.GetData();
}

void UMyGameInstance::Init()
{
	Super::Init();

	//구조체로 관리되는 학생데이터

	//Emplace를 이용한 300명의 학생 생성
	constexpr int32 StudentNum = 300;
	for (int32 i = 1; i <= StudentNum; ++i)
	{
		StudentsData.Emplace(MakeRandomName(), i);
	}

	//TArray를 이용한 이름 복사
	TArray<FString> AllStudentsNames;
	Algo::Transform(StudentsData, AllStudentsNames,
		[](const FStudentData& Val)
		{
			return Val.Name;
		});

	UE_LOG(LogTemp, Log, TEXT("모든 학생 이름의 수 : %d"), AllStudentsNames.Num());

	//TArray를 이용한 이름 복사
	TSet<FString> AllUniqueNames;
	Algo::Transform(StudentsData, AllUniqueNames,
		[](const FStudentData& Val)
		{
			return Val.Name;
		});

	UE_LOG(LogTemp, Log, TEXT("중복 없는 이름의 수 : %d"), AllUniqueNames.Num());

	//TMap에 Order를 Key로 값 복사
	Algo::Transform(StudentsData, StudentsMap,
		[](const FStudentData& Val)
		{
			return TPair<int32, FString>(Val.Order, Val.Name);
		});

	UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 맵의 레코드 수 : %d"), StudentsMap.Num());

	//TMap에 이름을 Key로 값 복사
	TMap<FString, int32> StudentsUniqueMapByName;
	Algo::Transform(StudentsData, StudentsUniqueMapByName,
		[](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		});

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 맵의 레코드 수 : %d"), StudentsUniqueMapByName.Num());

	//MultiTMap에 이름을 Key로 값 복사
	TMultiMap<FString, int32> StudentsMapByName;
	Algo::Transform(StudentsData, StudentsMapByName,
		[](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		});

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 멀티 맵의 레코드 수 : %d"), StudentsUniqueMapByName.Num());

	//중복된 Key값의 갯수 찾기
	const FString TargetName(TEXT("이혜은"));
	TArray<int32> AllOrders;
	StudentsMapByName.MultiFind(TargetName, AllOrders);

	UE_LOG(LogTemp, Log, TEXT("이름이 %s인 학생 수 : %d"), *TargetName, AllOrders.Num());

	//TSet의 DefaultKeyFuncs
	TSet<FStudentData> StudentsSet;
	for (int32 i = 1; i <= StudentNum; ++i)
	{
		//'GetTypeHash': none of the 1267 overloads could convert all the argument types -> 에러 발생
		//이유는? 1267개의 모든 오버로드 함수를 찾아본 결과 FStudentData에 맞는 GetTypeHash함수를 찾지 못했다는 뜻!
		//이경우에는 GetTypeHash가 가능하도록 추가 기능을 넣어줘야함!
		StudentsSet.Emplace(FStudentData(MakeRandomName(), i));
	}
}
