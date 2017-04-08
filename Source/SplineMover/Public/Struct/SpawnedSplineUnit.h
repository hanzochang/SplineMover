// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SplineComponent.h"
#include "SplineUnit.h"
#include "AssignedSplineUnitPoint.h"
#include "SpawnedSplineUnitActor.h"
#include "SpawnedSplineUnit.generated.h"

USTRUCT(BlueprintType)
struct SPLINEMOVER_API FSpawnedSplineUnit
{
	GENERATED_BODY()

public:
	FSplineUnit SplineUnit;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	FVector NextSpawnPoint;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	float Length;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    TArray<FAssignedSplineUnitPoint> AssignedSplineUnitPoints;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    TArray<FSpawnedSplineUnitActor> SpawnedSplineUnitActors;

public:
	static FSpawnedSplineUnit GenerateSpawnedSplineUnit(FSplineUnit &InSplineUnit);

public:
	void PushAssignedSplineUnitPoints(USplineComponent *Spline, int32 PointsIndex);

	void PushSpawnedSplineUnitActor(AActor* SpawnedActor);

	TArray<FVector> DeriveSplinePointsAddTo(FVector StartPoint, FVector PrevDirection, FRotator PrevRotation);

	void DeriveNextSpawnPoint(FSpawnedSplineUnit &SpawnedSplineUnit);

	void Destroy();


};
