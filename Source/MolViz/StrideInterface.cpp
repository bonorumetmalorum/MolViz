// Fill out your copyright notice in the Description page of Project Settings.


#include "StrideInterface.h"

FStrideInterface::FStrideInterface()
{
	Command = TEXT("C:/Program Files (x86)/University of Illinois/VMD/stride_WIN32.exe");
	FWindowsPlatformProcess::CreatePipe(RPipe, WPipe);
}

FStrideInterface::~FStrideInterface()
{
	if(FWindowsPlatformProcess::IsProcRunning(Handle))
	{
		FWindowsPlatformProcess::WaitForProc(Handle);
		FWindowsPlatformProcess::ClosePipe(RPipe, WPipe);
		FWindowsPlatformProcess::TerminateProc(Handle);
	}
}

FString FStrideInterface::RunStrideCommand(FString & PdbFile)
{
	Handle = FWindowsPlatformProcess::CreateProc(Command,  *PdbFile, false, true, true, &ProcID, 2, 0, WPipe, RPipe);
	return FWindowsPlatformProcess::ReadPipe(RPipe);
}
