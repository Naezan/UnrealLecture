// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Programmer.generated.h"

USTRUCT()
struct FSkill
{
	GENERATED_BODY()

	FSkill() {}
	FSkill(const FString& InName, int32 InCareer) : Name(InName), Career(InCareer) {}

	FString Name = TEXT("DefaultSkill");
	int32 Career = -1;
};

USTRUCT()
struct FProgrammerCareer
{
	GENERATED_BODY()

	void PrintSkills();

	FString Name = TEXT("¾Æ¹«°³");
	int32 Years = -1;
	int32 Career = -1;

	UPROPERTY()
	TArray<FSkill> Skills;
};

/**
 *
 */
UCLASS()
class UNREALSERIALIZATION_API UProgrammer : public UObject
{
	GENERATED_BODY()

public:
	UProgrammer();

	void PrintProgrammerData();

public:
	FProgrammerCareer ProgrammerCareer;
};
