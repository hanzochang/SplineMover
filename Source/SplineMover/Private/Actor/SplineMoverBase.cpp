// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineMoverPrivatePCH.h"
#include "SplineMoverBase.h"

// Sets default values
ASplineMoverBase::ASplineMoverBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<UStaticMeshComponent>(FName("SM")));

    Spline = CreateDefaultSubobject<USplineComponent>(FName("Spline"));
	Spline->SetupAttachment(StaticMesh);

    ProceduralSplineDirector = CreateDefaultSubobject<UProceduralSplineDirector>(FName("SplineDirector"));
    ProceduralSplinePointBuilder = CreateDefaultSubobject<UProceduralSplinePointBuilder>(FName("SplinePointBuilder"));
    ProceduralSplineActorsBuilder = CreateDefaultSubobject<UProceduralSplineActorsBuilder>(FName("SplineActorsBuilder"));
	SplineMoverEntity = FSplineMoverEntity(2);

	DeletedSplineLengthsDiff = 0;

	SplineUnits = SplineUnitGenerator->GenerateSplineUnits("splinetest.json");
}

// Called when the game starts or when spawned
void ASplineMoverBase::BeginPlay()
{
	Super::BeginPlay();
	ProceduralSplineDirector->Initialize(
		Spline,
		SplineUnits,
		SpawnedSplineUnits,
		DeletedSplineLengthsDiff,
		SplineMoverEntity,
		ProceduralSplinePointBuilder,
		ProceduralSplineActorsBuilder
	);

	ProceduralSplineDirector->CreateInitialSpline();
}

void ASplineMoverBase::WatchSplineLifeCycle(float CurrentLength)
{
	ProceduralSplineDirector->CheckSplineMoverEntity(CurrentLength);
}

FVector ASplineMoverBase ::GetCurrentLocationAlongSpline(float distance)
{
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, FString::SanitizeFloat(ProceduralSplineDirector->DeletedSplineLengthsDiff)); }
	return Spline->GetWorldLocationAtDistanceAlongSpline(distance - ProceduralSplineDirector->DeletedSplineLengthsDiff);
}

FVector ASplineMoverBase::GetCurrentDirectionAlongSpline(float distance)
{
	return Spline->GetWorldDirectionAtDistanceAlongSpline(distance - ProceduralSplineDirector->DeletedSplineLengthsDiff);
}

FRotator ASplineMoverBase::GetCurrentRotationAlongSpline(float distance)
{
	return Spline->GetWorldRotationAtDistanceAlongSpline(distance - ProceduralSplineDirector->DeletedSplineLengthsDiff);
}