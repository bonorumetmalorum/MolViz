// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "RepresentationFactory.generated.h"

class AProteinData;
class AProteinRepresentation;
class UVDW;
/**
 * 
 */
UCLASS()
class MOLVIZ_API URepresentationFactory : public UFactory
{
	GENERATED_BODY()

public:

	URepresentationFactory();

	bool DoesSupportClass(UClass* Class) override;

	UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;

	UVDW* CreateNewVdwRep(AProteinRepresentation* InParent, AProteinData * InProteinData, /*TODO pass in protein rep selections*/ FName InName) const;

private:
	//TODO: UCPK* CreateNewCPKRep(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext);
	
};
