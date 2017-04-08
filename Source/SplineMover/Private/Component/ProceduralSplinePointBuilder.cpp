// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineMoverPrivatePCH.h"
#include "ProceduralSplinePointBuilder.h"

void UProceduralSplinePointBuilder::AssignPointsToSpline(
	USplineComponent *Spline,
	FSpawnedSplineUnit &SpawnedSplineUnit,
	FVector &StartPoint
)
{
	FVector PrevDirection = Spline->GetDirectionAtSplinePoint(Spline->GetNumberOfSplinePoints(), ESplineCoordinateSpace::Type::Local);
	FRotator PrevRotation  = Spline->GetRotationAtSplinePoint(Spline->GetNumberOfSplinePoints(), ESplineCoordinateSpace::Type::Local);

	TArray<FVector> SplinePoints = SpawnedSplineUnit.DeriveSplinePointsAddTo(StartPoint, PrevDirection, PrevRotation);

	for (FVector SplinePoint : SplinePoints) {
		Spline->AddSplinePoint(SplinePoint, ESplineCoordinateSpace::Type::Local);
		SpawnedSplineUnit.PushAssignedSplineUnitPoints(Spline, Spline->GetNumberOfSplinePoints());
	}

}