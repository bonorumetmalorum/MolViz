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
}

UVDW* URepresentationFactory::CreateNewVdwRep(AProteinData * InProteinData, FName InName) const
{
	UVDW* rep = NewObject<UVDW>(InProteinData->GetRepresentation().Get(), InName);
	InProteinData->GetRepresentation()->Representations.Add(TWeakObjectPtr<URepresentation>(rep));
	rep->AttachToComponent(InProteinData->GetRepresentation().Get()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	rep->SetSphereRes(10, 10, 10.f);
	//TODO pass in selection data
	rep->ConstructRepresentation(InProteinData);
	return rep;
}

UCPK* URepresentationFactory::CreateNewCpkRep(AProteinRepresentation* InParent, AProteinData* InProteinData, FName InName) const
{
	UCPK* rep = NewObject<UCPK>(InParent, InName);
	InProteinData->GetRepresentation()->Representations.Add(TWeakObjectPtr<URepresentation>(rep));
	//rep->Config(5, 5, 0.2f, 0.1f, 5, 5);
	rep->AttachToComponent(InParent->GetRootComponent(),FAttachmentTransformRules::SnapToTargetIncludingScale);
	//rep->SetWorldTransform(InParent->GetActorTransform());
	rep->ConstructRepresentation(InProteinData);
	return rep;
}

UTubeRepresentation* URepresentationFactory::CreateNewTubeRep(AProteinRepresentation* InParent, AProteinData* InProteinData, FName InName) const
{
	UTubeRepresentation* rep = NewObject<UTubeRepresentation>(InParent, InName);
	InProteinData->GetRepresentation()->Representations.Add(TWeakObjectPtr<URepresentation>(rep));
	rep->ConstructRepresentation(InProteinData);
	rep->AttachToComponent(InParent->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	//rep->SetWorldTransform(InParent->GetActorTransform());
	return rep;
}

UNewCartoonRepresentation* URepresentationFactory::CreateNewNCartoonRep(AProteinRepresentation* InParent,
	AProteinData* const InProteinData, FName InName)
{
	UNewCartoonRepresentation* rep = NewObject<UNewCartoonRepresentation>(InParent, InName);
	InProteinData->GetRepresentation()->Representations.Add(TWeakObjectPtr<URepresentation>(rep));
	rep->SetWorldLocation(InProteinData->FindCOM());
	rep->ConstructRepresentation(InProteinData);
	rep->AttachToComponent(InParent->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	return rep;
}
