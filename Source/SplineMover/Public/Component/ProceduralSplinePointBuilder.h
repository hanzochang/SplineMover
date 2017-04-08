// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PrimitiveComponent.h"
#include "SplineUnit.h"
#include "SpawnedSplineUnit.h"
#include "Components/SplineComponent.h"
#include "ProceduralSplinePointBuilder.generated.h"

/**
 * 
 */
UCLASS()
class SPLINEMOVER_API UProceduralSplinePointBuilder : public UPrimitiveComponent
{
	GENERATED_BODY()
	
public:
	void AssignPointsToSpline(
		USplineComponent *Spline,
		FSpawnedSplineUnit &SpawnedSplineUnit,
		FVector &StartPoint
	);
};