// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpawnableActor.h"
#include "SplineUnit.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESplineUnit : uint8
{
    WAVE_LINEAR      UMETA(DisplayName = "Linear"),
    WAVE_SIN         UMETA(DisplayName = "Sin"),
    WAVE_TRIANGLE    UMETA(DisplayName = "Triangle"),
    WAVE_SAWTOOTH    UMETA(DisplayName = "Sawtooth")
};

FString GetSplineUnitEnumAsString(ESplineUnit EnumValue);

USTRUCT(BlueprintType)
struct SPLINEMOVER_API FSplineUnit
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    ESplineUnit WaveType;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    FRotator UnitRotator;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	bool InheritRotatorPitch;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	bool InheritRotatorYaw;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	bool InheritRotatorInRoll;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    float Scalar;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 Density;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	FRotator CurveUnitRotator;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    float CurveScalar;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    float WaveFreq;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    float Msec;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    int32 loop;
    
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    TArray<FSpawnableActor> SpawnableActors;

public:
	static FSplineUnit GenerateSplineUnit(
		ESplineUnit WaveType,
		FRotator UnitRotator,
		bool InheritRotatorPitch,
		bool InheritRotatorYaw,
		bool InheritRotatorInRoll,
		float Scalar,
		int32 Density,
		FRotator CurveUnitVector,
		float CurveScalar,
		float WaveFreq,
		float Msec,
		int32 loop,
		TArray<FSpawnableActor> SpawnableActors
	);

public:
	FString ToDebugString();
	float ScalarPerPoint();
	FVector UnitVector(FRotator PrevRotation);
	FVector CurveUnitVector(FRotator PrevRotation);

	TArray<FVector> DeriveSplinePointsAddTo(
		                         FVector PrevPoint = FVector{ 0,0,0 },
								 FVector PrevDirection = FVector{ 0,0,0 },
								 FRotator PrevRotation = FRotator{ 0,0,0 });

	FVector DeriveNextSplineUnitStartPoint(FVector PrevPoint = FVector{ 0,0,0 },
										   FVector PrevDirection = FVector{ 0,0,0 },
										   FRotator PrevRotation = FRotator{ 0,0,0 });

private:
	FRotator InheritableRotator(FRotator PrevRotation);

	TArray<FVector> DeriveWaveLinearPoints(FVector PrevPoint,
										   FVector PrevDirection, FRotator PrevRotation);

	TArray<FVector> DeriveWaveSinPoints(FVector PrevPoint,
							            FVector PrevDirection, FRotator PrevRotation);

};