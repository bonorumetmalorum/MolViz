// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * STRIDE interface class
 * calls stride as a subprocess and reads from output from stdout
 */
class MOLVIZ_API FStrideInterface
{
public:
	FStrideInterface();
	~FStrideInterface();

	/**
	 * run the STRIDE program with the given pdb file
	 * @param PdbFile the pdb file to process
	 * @return the STRIDE program output
	 */
	FString RunStrideCommand(FString & PdbFile);
	const TCHAR* Command;
	uint32 ProcID = 0;
	void* RPipe;
	void* WPipe;
	FProcHandle Handle;
};
