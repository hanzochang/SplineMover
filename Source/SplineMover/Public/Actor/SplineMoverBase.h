// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SplineUnit.h"
#include "SpawnedSplineUnit.h"
#include "SplineUnitGenerator.h"
#include "SplineMoverEntity.h"
#include "ProceduralSplineDirector.h"
#include "ProceduralSplinePointBuilder.h"
#include "ProceduralSplineActorsBuilder.h"
#include "Components/SplineComponent.h"
#include "SplineMoverBase.generated.h"

UCLASS(Blueprintable)
class SPLINEMOVER_API ASplineMoverBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineMoverBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void Tick( float DeltaSeconds ) override;

public:

	UPROPERTY(VisibleAnyWhere)
	USplineComponent* Spline;

	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* StaticMesh;

	TArray<FSplineUnit> SplineUnits;
	FSplineMoverEntity SplineMoverEntity;
	TArray<FSpawnedSplineUnit> SpawnedSplineUnits;

	USplineUnitGenerator* SplineUnitGenerator;

	UProceduralSplineDirector* ProceduralSplineDirector;
	UProceduralSplinePointBuilder* ProceduralSplinePointBuilder;
	UProceduralSplineActorsBuilder* ProceduralSplineActorsBuilder;

	// è¡ãéÇµÇΩSpawnedSplineUnitÇÃLengthÇÃó›åv
	float DeletedSplineLengthsDiff;

public:	
	UFUNCTION(BlueprintCallable, Category=General)
	void WatchSplineLifeCycle(float CurrentLength);

	UFUNCTION(BlueprintCallable, Category=General)
	FVector GetCurrentLocationAlongSpline(float distance);

	UFUNCTION(BlueprintCallable, Category=General)
	FRotator GetCurrentRotationAlongSpline(float distance);

	UFUNCTION(BlueprintCallable, Category=General)
	FVector GetCurrentDirectionAlongSpline(float distance);

};