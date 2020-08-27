// Fill out your copyright notice in the Description page of Project Settings.


#include "MolVizGauntletTestController.h"


#include "BenchmarkGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UMolVizGauntletTestController::StartTesting()
{
	StartProfiling();
}

void UMolVizGauntletTestController::StartProfiling()
{
	FCsvProfiler::Get()->BeginCapture();
}

void UMolVizGauntletTestController::StopProfiling()
{
    UE_LOG(LogGauntlet, Display, TEXT("Stopping the profiler"));

    TSharedFuture<FString> future = FCsvProfiler::Get()->EndCapture();

    // launch an async task that polls the Future for completion
    // will in turn launch a task on the game thread once the CSV file is saved to disk
    AsyncTask(ENamedThreads::AnyThread, [this, future]()
    {
        while (!future.IsReady())
            FPlatformProcess::SleepNoStats(0);

        AsyncTask(ENamedThreads::GameThread, [this]()
        {
            StopTesting();
        }
        );
    }
    );
}

void UMolVizGauntletTestController::StopTesting()
{
	EndTest();
}

void UMolVizGauntletTestController::OnInit()
{
	UE_LOG(LogGauntlet, Display, TEXT("YourGameGauntletController started"));
    StartProfiling();
}

void UMolVizGauntletTestController::OnTick(float DeltaTime)
{
    if(Cast<ABenchmarkGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->IsFinished)
    {
        StopProfiling();
    }
}
