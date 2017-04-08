// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineMoverPrivatePCH.h"
#include "SpawnedSplineUnitActor.h"

FSpawnedSplineUnitActor FSpawnedSplineUnitActor::Generate(AActor* SpawnedObject)
{
	FSpawnedSplineUnitActor FSpawnedSplineUnitActor;
	FSpawnedSplineUnitActor.SpawnedObject = SpawnedObject;

	return FSpawnedSplineUnitActor;
}

void FSpawnedSplineUnitActor::Destroy()
{
	SpawnedObject->Destroy();
}
