// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "MaterialInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class MOLVIZ_API UMaterialInstanceBase : public UMaterialInstanceDynamic
{
	GENERATED_BODY()

public:
	UMaterialInstanceBase();

	int Ambient;
	int Diffuse;
	int Specular;
	int Shininess;
	int Mirror;
	int Opacity;
	int Outline;
	int OutlineWidth;
};
