// Fill out your copyright notice in the Description page of Project Settings.


#include "StrideInterface.h"

FStrideInterface::FStrideInterface()
{
	Command = *(FGenericPlatformMisc::GetEnvironmentVariable(TEXT("Stride")));
	FGenericPlatformProcess::CreatePipe(RPipe, WPipe);
}

FStrideInterface::~FStrideInterface()
{
	if(FGenericPlatformProcess::IsProcRunning(Handle))
	{
		FGenericPlatformProcess::WaitForProc(Handle);
		FGenericPlatformProcess::ClosePipe(RPipe, WPipe);
		FGenericPlatformProcess::TerminateProc(Handle);
	}
}

FString FStrideInterface::RunStrideCommand(FString & PdbFile)
{
	Handle = FGenericPlatformProcess::CreateProc(Command,  *PdbFile, false, true, true, &ProcID, 2, 0, WPipe, RPipe);
	return FGenericPlatformProcess::ReadPipe(RPipe);
}
