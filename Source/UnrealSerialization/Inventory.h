// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

/**
 *
 */
UCLASS()
class UNREALSERIALIZATION_API UInventory : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int32 ItemCount;

	UPROPERTY()
		FString InventorySlotName;
};
