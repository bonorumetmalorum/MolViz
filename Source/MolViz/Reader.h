// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Base functionality that all readers must implement
 */
class MOLVIZ_API IReader
{
public:
	IReader();
	virtual ~IReader();
	virtual void read(FString filepath) = 0;
protected:
	bool ReadLine(IFileHandle * Data, uint8* OutData, SIZE_T maxRead);
	FString BytesToString(const uint8* bytes, SIZE_T count);
};
