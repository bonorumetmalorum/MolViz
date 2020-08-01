// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GauntletTestController.h"
#include "MolVizGauntletTestController.generated.h"

/**
 * 
 */
UCLASS()
class MOLVIZ_API UMolVizGauntletTestController : public UGauntletTestController
{
	GENERATED_BODY()

	//create functions to start profiling
	//create functions to stop profiling
	//create enum to represent state
	//	adding representation
	//		add CPK, Add New Cartoon remove VDW.
	//	hiding representation
	//		not really needed, I think we need to Apply CPK and New Cartoon and or Tube. Because the biochemists would want to see how the protein deforms, etc.
	//  we at least need to try and rotate??
	//	rotating
	//		apply a rotation directly to the AProteinRep actor rather than control the movement via the player controller
	//	dont do the following if its too time consuming
	//	translating
	//	scaling
	//	start
	//		load the molecule, start the csv perf tool
	//	stop
	//		the gauntlet test is complete, we can shut down, saving any currently running csv perf
	//	restart
	//		we need this one because we want to stop recording, remove the molecule and restart recording, repeating from the first state machine node
	//		
};
