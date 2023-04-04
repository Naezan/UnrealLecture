// Fill out your copyright notice in the Description page of Project Settings.


#include "Programmer.h"

UProgrammer::UProgrammer()
{
}

void UProgrammer::PrintProgrammerData()
{
	UE_LOG(LogTemp, Log, TEXT("ProgrammerName : %s, Years : %d, Career : %d"), 
	*ProgrammerCareer.Name, ProgrammerCareer.Years, ProgrammerCareer.Career);

	ProgrammerCareer.PrintSkills();
}

void FProgrammerCareer::PrintSkills()
{
	for (const auto& Skill : Skills)
	{
		UE_LOG(LogTemp, Log, TEXT("SkillName : %s, SkillCareer : %d"),
			*Skill.Name, Skill.Career);
	}
}
