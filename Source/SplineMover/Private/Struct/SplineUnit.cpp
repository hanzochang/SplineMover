// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineMoverPrivatePCH.h"
#include "SplineUnit.h"

/**
 * Converts a ESplineUnit to String.
 * 
 * @param	EplineUnit
 * @returns String
 */

FString GetSplineUnitEnumAsString(ESplineUnit EnumValue)
{
  const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ESplineUnit"), true);
  if(!EnumPtr) return FString("Invalid");
 
  return EnumPtr->GetEnumName((int32)EnumValue);
};

/**
 * Converts a FSplineUnit to String.
 * 
 * @param	SplineUnit		SplineUnit members to sanitize
 * @returns String
 */

FString FSplineUnit::ToDebugString()
{
	FString Result;
	Result =
		"UnitRotator: " + UnitRotator.ToString() + "  |   " +
		"InheritRotatorPitch: " + (InheritRotatorPitch ? "true" : "false" ) + "  |   " +
		"InheritRotatorYaw: " + (InheritRotatorYaw ? "true" : "false" ) + "  |   " +
		"InheritRotatorInRoll: " + (InheritRotatorInRoll ? "true" : "false" ) + "  |   " +
		"Scalar: " + FString::SanitizeFloat(Scalar) + "  |   " +
		"Density" + FString::FromInt(Density) + "  |   " +
		"CurveUnitRotator: " + CurveUnitRotator.ToString() + "  |   " +
		"CurveScalar: " + FString::SanitizeFloat(CurveScalar) + "  |   " +
		"WaveFreq: " + FString::FromInt(WaveFreq) + "  |   " +
		"Msec: " + FString::SanitizeFloat(Msec) + "  |   " +
		"loop: " + FString::FromInt(loop);
		//"WaveType: " + WaveType
		//"SpawnableActors: " + SpawnableActors

	return Result;
}

float FSplineUnit::ScalarPerPoint()
{
	return Scalar / Density;
}

FSplineUnit FSplineUnit::GenerateSplineUnit(
		ESplineUnit WaveType,
		FRotator UnitRotator,
		bool InheritRotatorPitch,
		bool InheritRotatorYaw,
		bool InheritRotatorInRoll,
		float Scalar,
		int32 Density,
		FRotator CurveUnitRotator,
		float CurveScalar,
		float WaveFreq,
		float Msec,
		int32 loop,
		TArray<FSpawnableActor> SpawnableActors
)
{
	FSplineUnit SplineUnit;
	SplineUnit.WaveType = WaveType;
	SplineUnit.UnitRotator = UnitRotator;
	SplineUnit.InheritRotatorPitch = InheritRotatorPitch;
	SplineUnit.InheritRotatorYaw = InheritRotatorYaw;
	SplineUnit.InheritRotatorInRoll = InheritRotatorInRoll;
	SplineUnit.Scalar = Scalar;
	SplineUnit.Density = Density;
	SplineUnit.CurveUnitRotator = CurveUnitRotator;
	SplineUnit.CurveScalar = CurveScalar;
	SplineUnit.WaveFreq = WaveFreq;
	SplineUnit.Msec = Msec;
	SplineUnit.loop = loop;
	SplineUnit.SpawnableActors = SpawnableActors;

	return SplineUnit;
}

FVector FSplineUnit::UnitVector(FRotator PrevRotation)
{
	return (UnitRotator + InheritableRotator(PrevRotation)).Vector();
}


FVector FSplineUnit::CurveUnitVector(FRotator PrevRotation)
{
	return (UnitRotator + CurveUnitRotator + InheritableRotator(PrevRotation)).Vector();
}

TArray<FVector> FSplineUnit::DeriveSplinePointsAddTo(FVector PrevPoint,
	                                      FVector PrevDirection, FRotator PrevRotation)
{
	TArray<FVector> Points;

	switch (WaveType)
	{
	case ESplineUnit::WAVE_LINEAR:
		Points = DeriveWaveLinearPoints(PrevPoint, PrevDirection, PrevRotation);
		break;
	case ESplineUnit::WAVE_SIN:
		Points = DeriveWaveSinPoints(PrevPoint, PrevDirection, PrevRotation);
		break;
	case ESplineUnit::WAVE_SAWTOOTH:
		// pending
		Points = DeriveWaveLinearPoints(PrevPoint, PrevDirection, PrevRotation);
		break;
	}

	return Points;
}

FVector FSplineUnit::DeriveNextSplineUnitStartPoint(FVector PrevPoint, FVector PrevDirection, FRotator PrevRotation)
{
	FVector Point;

	switch (WaveType)
	{
	case ESplineUnit::WAVE_LINEAR:
		Point = (PrevPoint + (UnitVector(PrevRotation) * ScalarPerPoint() * (Density + 1)));
		break;

	case ESplineUnit::WAVE_SIN:
		// TODO Spiit to anothor method
		float VertexBase = FMath::Sin(PI / Density * (Density + 1) * WaveFreq);
		FVector Uv = UnitVector(PrevRotation);
		FVector Cuv = CurveUnitVector(PrevRotation);

		Point = PrevPoint + (Uv * ScalarPerPoint() * (Density + 1)) + (Cuv * CurveScalar * VertexBase);
		break;
	}

	return Point;
}


/**
* private
*/

FRotator FSplineUnit::InheritableRotator(FRotator PrevRotation)
{
	float RotationYaw = InheritRotatorYaw ? PrevRotation.Yaw : 0;
	float RotationPitch = InheritRotatorPitch ? PrevRotation.Pitch : 0;
	float RotationInRoll = InheritRotatorInRoll ? PrevRotation.Roll : 0;
	return FRotator{ RotationPitch, RotationYaw, RotationInRoll };
}

TArray<FVector> FSplineUnit::DeriveWaveLinearPoints(FVector PrevPoint, FVector PrevDirection, FRotator PrevRotation)
{
	TArray<FVector> Points;

	for (auto i = 0; i <= Density; i++)
	{
		Points.Push(PrevPoint + (UnitVector(PrevRotation) * ScalarPerPoint() * i));
	}

	return Points;
}

TArray<FVector> FSplineUnit::DeriveWaveSinPoints(FVector PrevPoint, FVector PrevDirection, FRotator PrevRotation)
{
	// TODO Spiit to anothor method
	TArray<FVector> Points;
	FVector Uv = UnitVector(PrevRotation);
	FVector Cuv = CurveUnitVector(PrevRotation);

	for (auto i = 0; i <= Density; i++)
	{
		float VertexBase = FMath::Sin(PI / Density * i * WaveFreq);
		Points.Push(PrevPoint + (Uv * ScalarPerPoint() * i) + (Cuv * CurveScalar * VertexBase));
	}

	return Points;
}