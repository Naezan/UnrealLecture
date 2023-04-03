// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "JsonObjectConverter.h"
#include "Programmer.h"

void PrintStudentInfo(const UStudent* InStudent, const FString& InTag)
{
	UE_LOG(LogTemp, Log, TEXT("[%s] 이름 %s, 순번 %d"), *InTag, *InStudent->GetName(), InStudent->GetOrder());
}

UMyGameInstance::UMyGameInstance()
{
}

void UMyGameInstance::Init()
{
	Super::Init();

	FStudentData RawDataSrc(16, TEXT("내잔스"));

	const FString SavedDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
	UE_LOG(LogTemp, Log, TEXT("저장할 파일 폴더 경로 : %s"), *SavedDir);

	{
		const FString RawDataFimeName(TEXT("RawDat.bin"));
		FString RawDataAbsolutePath = FPaths::Combine(*SavedDir, *RawDataFimeName);
		UE_LOG(LogTemp, Log, TEXT("저장할 파일 경로 : %s"), *RawDataAbsolutePath);
		FPaths::MakeStandardFilename(RawDataAbsolutePath);
		UE_LOG(LogTemp, Log, TEXT("저장할 파일 경로 : %s"), *RawDataAbsolutePath);

		FArchive* RawFileWriterAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath);
		if (nullptr != RawFileWriterAr)
		{
			*RawFileWriterAr << RawDataSrc;
			RawFileWriterAr->Close();
			delete RawFileWriterAr;
			RawFileWriterAr = nullptr;
		}

		FStudentData RawDataDest;
		FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbsolutePath);
		if (nullptr != RawFileReaderAr)
		{
			*RawFileReaderAr << RawDataDest;
			RawFileReaderAr->Close();
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;

			UE_LOG(LogTemp, Log, TEXT("[RawData] 이름 : %s, 순번 : %d"), *RawDataDest.Name, RawDataDest.Order);
		}
	}

	StudentSrc = NewObject<UStudent>();
	StudentSrc->SetName(TEXT("내잔"));
	StudentSrc->SetOrder(15);

	{
		const FString ObjectDataFileName(TEXT("ObjectData.bin"));
		FString ObjectDataAbsolutePath = FPaths::Combine(*SavedDir, *ObjectDataFileName);
		FPaths::MakeStandardFilename(ObjectDataAbsolutePath);

		//버퍼
		TArray<uint8> BufferArray;
		FMemoryWriter MemoryWriterAr(BufferArray);
		//BufferArray에 직렬화
		StudentSrc->Serialize(MemoryWriterAr);

		if (TUniquePtr<FArchive> FileWriterAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataAbsolutePath)))
		{
			//파일에 BufferArray데이터 직렬화
			*FileWriterAr << BufferArray;
			FileWriterAr->Close();
		}

		TArray<uint8> BufferArrayFromFile;
		if (TUniquePtr<FArchive> FileReaderAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*ObjectDataAbsolutePath)))
		{
			//파일의 데이터를 BufferArray에 역직렬화
			*FileReaderAr << BufferArrayFromFile;
			FileReaderAr->Close();
		}

		//StudentDest에 BufferArrayFromFile데이터 역직렬화
		FMemoryReader MemoryReaderAr(BufferArrayFromFile);
		UStudent* StudentDest = NewObject<UStudent>();
		StudentDest->Serialize(MemoryReaderAr);
		PrintStudentInfo(StudentDest, TEXT("ObjectData"));
	}

	{
		FString JsonDataFileName(TEXT("StudentJsonData.txt"));
		FString JsonDataAbsolutePath = FPaths::Combine(*SavedDir, *JsonDataFileName);
		FPaths::MakeStandardFilename(JsonDataAbsolutePath);

		TSharedRef<FJsonObject> JsonObjectSrc = MakeShared<FJsonObject>();
		//Object를 Json 형식으로 만들어서 JsonObjectSrc에 넣어준다.
		FJsonObjectConverter::UStructToJsonObject(StudentSrc.GetClass(), StudentSrc, JsonObjectSrc);

		FString JsonOutString;
		//JsonArchive생성
		TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr = TJsonWriterFactory<TCHAR>::Create(&JsonOutString);
		//JsonObject를 파일에 저장
		if (FJsonSerializer::Serialize(JsonObjectSrc, JsonWriterAr))
		{
			FFileHelper::SaveStringToFile(JsonOutString, *JsonDataAbsolutePath);
		}

		//Json파일을 String으로 로드
		FString JsonInString;
		FFileHelper::LoadFileToString(JsonInString, *JsonDataAbsolutePath);

		//JsonArchive생성
		TSharedRef<TJsonReader<TCHAR>> JsonReaderAr = TJsonReaderFactory<TCHAR>::Create(JsonInString);

		//JsonObjectDest에 Json데이터를 로드
		TSharedPtr<FJsonObject> JsonObjectDest;
		if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectDest))
		{
			//JsonObject에서 UStruct로 변환후 JsonStudentObject에 로드
			UStudent* JsonStudentObject = NewObject<UStudent>();
			if (FJsonObjectConverter::JsonObjectToUStruct(JsonObjectDest.ToSharedRef(), JsonStudentObject->GetClass(), JsonStudentObject))
			{
				PrintStudentInfo(JsonStudentObject, TEXT("JsonData"));
			}
		}
	}

	//프로그래머 데이터 객체를 생성합니다.
	ProgrammerData = NewObject<UProgrammer>();
	ProgrammerData->ProgrammerCareer;

	//절대 경로를 생성합니다.
	FString JsonFileDir(TEXT("ProgrammerData.json"));
	FString JsonFileAbsolutePath = FPaths::Combine(*SavedDir, *JsonFileDir);
	FPaths::MakeStandardFilename(JsonFileAbsolutePath);

	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *JsonFileAbsolutePath);

	//JsonArchive생성
	TSharedRef<TJsonReader<TCHAR>> JsonReaderArchive = TJsonReaderFactory<TCHAR>::Create(JsonString);

	//JsonObjectDest에 Json데이터를 로드
	TSharedPtr<FJsonObject> JsonObject;
	if (FJsonSerializer::Deserialize(JsonReaderArchive, JsonObject))
	{
		auto Programmer = JsonObject->GetObjectField(TEXT("Programmer"));
		ProgrammerData->ProgrammerCareer.Name = Programmer->GetStringField(TEXT("Name"));
		ProgrammerData->ProgrammerCareer.Years = Programmer->GetIntegerField(TEXT("Years"));
		ProgrammerData->ProgrammerCareer.Career = Programmer->GetIntegerField(TEXT("Career"));

		for (const auto& Skill : Programmer->GetArrayField(TEXT("Skills")))
		{
			ProgrammerData->ProgrammerCareer.Skills.Emplace(
				Skill->AsObject()->GetStringField(TEXT("Name")),
				Skill->AsObject()->GetIntegerField(TEXT("Career"))
			);
		}

		ProgrammerData->PrintProgrammerData();
	}
}
