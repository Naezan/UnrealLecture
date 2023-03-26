// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 *
 */
UCLASS()
class UNREALCOMPOSITION_API UPerson : public UObject
{
	GENERATED_BODY()

public:
	UPerson();

	FORCEINLINE const FString& GetName() const { return Name; }
	FORCEINLINE void SetName(const FString& InName) { Name = InName; }

	//C++에선 구현부를 해더에 구현하면 암시적 inline이 된다. 하지만 언리얼에서는 잘 모르겠다
	class UCard* GetCard() const { return Card; }
	void SetCard(class UCard* InCard) { Card = InCard; }

protected:
	UPROPERTY()
		FString Name;

	UPROPERTY()
		TObjectPtr<class UCard> Card;

private:

};
