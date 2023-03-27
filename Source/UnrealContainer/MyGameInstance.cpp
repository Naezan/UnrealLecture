// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Algo/Accumulate.h"

void UMyGameInstance::Init()
{
	Super::Init();

	constexpr int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	for (int32 i = 1; i <= ArrayNum; ++i)
	{
		Int32Array.Add(i);
	}

	Int32Array.RemoveAll([](int32 Val) {
		return Val % 2 == 0;
		});

	Int32Array += {2, 4, 6, 8, 10};

	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = { 1,3,5,7,9,2,4,6,8,10 };
	Int32ArrayCompare.AddUninitialized(ArrayNum);
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);

	ensure(Int32Array == Int32ArrayCompare);

	int32 Sum = 0;
	for (const int32 Val : Int32Array)
	{
		Sum += Val;
	}

	ensure(Sum == 55);

	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);

	ensure(SumByAlgo == Sum);

	//TSet
	TSet<int32> Int32Set;
	for (int32 i = 1; i <= ArrayNum; ++i)
	{
		Int32Set.Add(i);
	}

	Int32Set.Remove(4);
	Int32Set.Remove(2);
	Int32Set.Remove(6);
	Int32Set.Remove(8);
	Int32Set.Remove(10);

	Int32Set.Add(2);
	Int32Set.Add(4);
	Int32Set.Add(6);
	Int32Set.Add(8);
	Int32Set.Add(10);
}
