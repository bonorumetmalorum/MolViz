// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MOLVIZ_API FStrideInterface
{
public:
	FStrideInterface();
	~FStrideInterface();

	FString RunStrideCommand(FString & PdbFile);
	const TCHAR* Command;
	uint32 ProcID = 0;
	void* RPipe;
	void* WPipe;
	FProcHandle Handle;
};
