// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialInstanceBase.h"

UMaterialInstanceBase::UMaterialInstanceBase()
{
	InitializeScalarParameterAndGetIndex("Ambient", 0.0, Ambient);
	InitializeScalarParameterAndGetIndex("Diffuse", 0.0, Diffuse);
	InitializeScalarParameterAndGetIndex("Specular", 0.0, Specular);
	InitializeScalarParameterAndGetIndex("Shininess", 0.0,  Shininess);
	InitializeScalarParameterAndGetIndex("Mirror", 0.0, Mirror);
	InitializeScalarParameterAndGetIndex("Opacity", 0.0,  Opacity);
	InitializeScalarParameterAndGetIndex("Outline", 0.0, Outline);
	InitializeScalarParameterAndGetIndex("OutlineWidth", 0.0, OutlineWidth);
}
