// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PrimitiveComponent.h"
#include "Components/SplineComponent.h"
#include "SplineUnit.h"
#include "SplineMoverEntity.h"
#include "ProceduralSplinePointBuilder.h"
#include "ProceduralSplineActorsBuilder.h"
#include "ProceduralSplineDirector.generated.h"

/**
 * 
 */
UCLASS()
class SPLINEMOVER_API UProceduralSplineDirector : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	USplineComponent *Spline;
	TArray<FSplineUnit> SplineUnits;
	TArray<FSpawnedSplineUnit> SpawnedSplineUnits;
	FSplineMoverEntity Entity;
	UProceduralSplinePointBuilder *ProceduralSplinePointBuilder;
	UProceduralSplineActorsBuilder *ProceduralSplineActorsBuilder;

	AActor *Owner;

	float DeletedSplineLengthsDiff;

	bool Refreshable;

public:
	void Initialize(
		USplineComponent *InSpline,
		TArray<FSplineUnit> &InSplineUnits,
		TArray<FSpawnedSplineUnit> &InSpawnedSplineUnits,
		float &InDeletedSplineLengthsDiff,
		FSplineMoverEntity &InEntity,
		UProceduralSplinePointBuilder *InProceduralSplinePointBuilder,
		UProceduralSplineActorsBuilder *InProceduralSplineActorsBuilder
	);

	void CreateInitialSpline();

	void CheckSplineMoverEntity(float CurrentLength);

private:
	void GenerateNextSpawnedSplineUnit();

	void RefreshEntityParameters();

	void DeleteFirstSpawnedSplineUnit();

	void UProceduralSplineDirector::UpdateSpline();

};