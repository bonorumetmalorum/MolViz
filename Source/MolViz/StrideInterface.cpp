// Fill out your copyright notice in the Description page of Project Settings.


#include "StrideInterface.h"

#include "HAL/FileManagerGeneric.h"
#if PLATFORM_LINUX
#include "Unix/UnixPlatformProcess.h"
#endif
FStrideInterface::FStrideInterface()
{
#if !UE_BUILD_SHIPPING
	//Command = TEXT("C:/Program Files (x86)/University of Illinois/VMD/stride_WIN32.exe");
	Command = TEXT(".\\stride_WIN32.exe");
#else
	Command = TEXT(".\\stride_WIN32.exe");
	UE_LOG(LogTemp, Warning, TEXT("SHIPPING"));
#endif
	
	//FWindowsPlatformProcess::CreatePipe(RPipe, WPipe);
}

FStrideInterface::~FStrideInterface()
{
#if PLATFORM_WINDOWS
	if(FWindowsPlatformProcess::IsProcRunning(Handle))
	{
		FWindowsPlatformProcess::TerminateProc(Handle);
		//FWindowsPlatformProcess::ClosePipe(RPipe, WPipe);
	}
#endif
#if PLATFORM_LINUX
	if (FLinuxPlatformProcess::IsProcRunning(Handle))
	{
		FLinuxPlatformProcess::TerminateProc(Handle);
		//FLinuxPlatformProcess::ClosePipe(RPipe, WPipe);
	}
#endif
}

FString FStrideInterface::RunStrideCommand(FString & PdbFile)
{
	FString StdOut, StdErr;
	int32 ReturnCode;
	FString Path = "\"" + PdbFile + "\"";
#if PLATFORM_WINDOWS
	bool Succ = FWindowsPlatformProcess::ExecProcess(Command,  *Path, &ReturnCode, &StdOut, &StdErr);
#endif
#if PLATFORM_LINUX
	bool Succ = FUnixPlatformProcess::ExecProcess(Command, *Path, &ReturnCode, &StdOut, &StdErr);
#endif

	if(!Succ)
	{
		UE_LOG(LogTemp, Warning, TEXT("stride failed with error code: %d and messsage %s"), ReturnCode, *StdErr)
	}
	//while(PipeOut.IsEmpty())
	//{
	//	PipeOut = FWindowsPlatformProcess::ReadPipe(RPipe);
	//}
	return StdOut;
}
