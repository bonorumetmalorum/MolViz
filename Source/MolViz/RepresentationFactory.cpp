// Fill out your copyright notice in the Description page of Project Settings.


#include "RepresentationFactory.h"
#include "ProteinRepresentation.h"
#include "AProteinData.h"
#include "VDW.h"
#include "CPK.h"
#include "Representation.h"
#include "TubeRepresentation.h"

URepresentationFactory::URepresentationFactory()
{
	bCreateNew = true;
	bEditorImport = true;
	bEditAfterNew = false;
	SupportedClass = TSubclassOf<URepresentation>();
}

bool URepresentationFactory::DoesSupportClass(UClass* Class)
{
	return Class->IsChildOf(SupportedClass);
}

/*
 * Builds a default representation which is VDW
 */
UObject* URepresentationFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	if(!InClass->IsChildOf(SupportedClass))
	{
		return nullptr;
	}
	UVDW * vdw = NewObject<UVDW>(InParent, InClass, InName, Flags);
	vdw->SetSphereRes(10, 10, 10.0f);
	return vdw;
}

UVDW* URepresentationFactory::CreateNewVdwRep(AProteinRepresentation* InParent, AProteinData * InProteinData, FName InName) const
{
	UVDW* rep = NewObject<UVDW>(InParent, InName);
	rep->SetSphereRes(10, 10, 10.f);
	//TODO pass in selection data
	rep->ConstructRepresentation(InProteinData);
	return rep;
}

UCPK* URepresentationFactory::CreateNewCpkRep(AProteinRepresentation* InParent, AProteinData* InProteinData, FName InName) const
{
	UCPK* rep = NewObject<UCPK>(InParent, InName);
	rep->AttachToComponent(InParent->GetRootComponent(),FAttachmentTransformRules::KeepWorldTransform);
	
	rep->Config(5, 5, 0.2f, 0.1f, 5, 5);
	rep->ConstructRepresentation(InProteinData);
	return rep;
}

UTubeRepresentation* URepresentationFactory::CreateNewTubeRep(AProteinRepresentation* InParent, AProteinData* InProteinData, FName InName) const
{
	UTubeRepresentation* rep = NewObject<UTubeRepresentation>(InParent, InName);
	rep->ConstructRepresentation(InProteinData);
	return rep;
}

UNewCartoonRepresentation* URepresentationFactory::CreateNewNCartoonRep(AProteinRepresentation* InParent,
	AProteinData* const InProteinData, const char* InName)
{
	UNewCartoonRepresentation* rep = NewObject<UNewCartoonRepresentation>(InParent, InName);
	rep->ConstructRepresentation(InProteinData);
	return rep;
}
