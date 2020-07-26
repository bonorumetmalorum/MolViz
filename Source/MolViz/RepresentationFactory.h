// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewCartoonRepresentation.h"
#include "TubeRepresentation.h"
#include "RepresentationFactory.generated.h"

class AProteinData;
class AProteinRepresentation;
class UVDW;
class UCPK;
/**
 * 
 */
UCLASS()
class MOLVIZ_API URepresentationFactory : public UObject
{
	GENERATED_BODY()

public:

	URepresentationFactory();
	
	UVDW* CreateNewVdwRep(AProteinData * InProteinData, /*TODO pass in protein rep selections*/ FName InName) const;
	UCPK* CreateNewCpkRep(AProteinRepresentation* InParent, AProteinData* InProteinData, FName InName) const;
	UTubeRepresentation* CreateNewTubeRep(AProteinRepresentation* InParent, AProteinData* InProteinData, FName InName) const;
	UNewCartoonRepresentation* CreateNewNCartoonRep(AProteinRepresentation* Cast, AProteinData* const ProteinData, FName InName);

private:
	
};
