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
 * Helper class used to create various representations
 */
UCLASS()
class MOLVIZ_API URepresentationFactory : public UObject
{
	GENERATED_BODY()

public:

	URepresentationFactory();
	/*
	 * create a new VDW representation
	 * @param InProteinData the protein data to represent
	 * @param InName the name to give to this new representation
	 * @return the newly created representation
	 */
	UVDW* CreateNewVdwRep(AProteinData * InProteinData, /*TODO pass in protein rep selections*/ FName InName) const;
	/*
	 * create a new CPK representation
	 * @param InParent the parent component
	 * @param InProteinData the protein data to represent
	 * @param InName the name to give to this new representation
	 * @return the newly created representation
	 */
	UCPK* CreateNewCpkRep(AProteinRepresentation* InParent, AProteinData* InProteinData, FName InName) const;
	/*
	 * create a new Tube representation
	 * @param InParent the parent component
	 * @param InProteinData the protein data to represent
	 * @param InName the name to give to this new representation
	 * @return the newly created representation
	 */
	UTubeRepresentation* CreateNewTubeRep(AProteinRepresentation* InParent, AProteinData* InProteinData, FName InName) const;
	/*
	 * create a new NCartoonRep representation
	 * @param InParent the parent component
	 * @param InProteinData the protein data to represent
	 * @param InName the name to give to this new representation
	 * @return the newly created representation
	 */
	UNewCartoonRepresentation* CreateNewNCartoonRep(AProteinRepresentation* InParent, AProteinData* const ProteinData, FName InName);

private:
	
};
