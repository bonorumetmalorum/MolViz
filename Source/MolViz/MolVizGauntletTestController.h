// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GauntletTestController.h"
#include "MolVizGauntletTestController.generated.h"

/**
 * pupeteering class for benchmark test automation
 */
UCLASS()
class MOLVIZ_API UMolVizGauntletTestController : public UGauntletTestController
{
	GENERATED_BODY()

private:


	/*
	 * start the test
	 */
	UFUNCTION()
	void StartTesting();
	/*
	 * start the profiling
	 */
	void StartProfiling();

	/*
	 * stop profiling
	 */
	UFUNCTION()
	void StopProfiling();

	/*
	 * stop testing the test is complete
	 */
	void StopTesting();

protected:
	/*
	 * called when the controller is created, setup test
	 */
	virtual void OnInit() override;
	/*
	 * called periodically, poll for completion
	 */
	virtual void OnTick(float DeltaTime) override;		
};
