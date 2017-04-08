// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SplineComponent.h"
#include "SpawnedSplineUnitActor.generated.h"

USTRUCT(BlueprintType)
struct SPLINEMOVER_API FSpawnedSplineUnitActor
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	AActor* SpawnedObject;

public:
	static FSpawnedSplineUnitActor Generate(AActor* SpawnedObject);

public:
	void Destroy();
};
