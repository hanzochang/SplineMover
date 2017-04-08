// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineMoverPrivatePCH.h"
#include "ProceduralSplineDirector.h"

void UProceduralSplineDirector::Initialize(
	USplineComponent *InSpline,
	TArray<FSplineUnit> &InSplineUnits,
	TArray<FSpawnedSplineUnit> &InSpawnedSplineUnits,
	float &InDeletedSplineLengthsDiff,
	FSplineMoverEntity &InEntity,
	UProceduralSplinePointBuilder *InProceduralSplinePointBuilder,
	UProceduralSplineActorsBuilder *InProceduralSplineActorsBuilder
)
{
	Spline = InSpline;
	SplineUnits = InSplineUnits;
	InSpawnedSplineUnits = InSpawnedSplineUnits;
	Entity = InEntity;
	ProceduralSplinePointBuilder = InProceduralSplinePointBuilder;
	ProceduralSplineActorsBuilder = InProceduralSplineActorsBuilder;

	DeletedSplineLengthsDiff = InDeletedSplineLengthsDiff;

	Refreshable = true;

    Owner = GetOwner();
}

void UProceduralSplineDirector::CreateInitialSpline()
{
	// 例外処理を書く。Builderがなかった場合 
	int32 counter = 0;
	FSpawnedSplineUnit PreviousSpawnedSplineUnit;
	float CurrentLength = 0;
	FVector StartPoint = FVector{ 0,0,0 };

	Entity.RearmostNextSpawnableCounter = 0; // TODO 要確認

	for (int32 i = 0; i < Entity.DisplayableSplineUnitSum(); i++)
	{
		CurrentLength = Spline->GetSplineLength();
		counter = i % SplineUnits.Num();
		
		FSplineUnit SplineUnit = SplineUnits[counter];
		FSpawnedSplineUnit SpawnedSplineUnit = FSpawnedSplineUnit::GenerateSpawnedSplineUnit(SplineUnit);

		ProceduralSplinePointBuilder->AssignPointsToSpline(Spline, SpawnedSplineUnit, StartPoint);
		ProceduralSplineActorsBuilder->SpawnActors(Owner, Spline, SpawnedSplineUnit);

		SpawnedSplineUnit.DeriveNextSpawnPoint(PreviousSpawnedSplineUnit);
		SpawnedSplineUnit.Length = Spline->GetSplineLength() - CurrentLength;
		StartPoint = SpawnedSplineUnit.NextSpawnPoint;

		SpawnedSplineUnits.Push(SpawnedSplineUnit);
		PreviousSpawnedSplineUnit = SpawnedSplineUnit;

		Entity.TopmostNextSpawnableCounter = i;
	}

	RefreshEntityParameters();
}

void UProceduralSplineDirector::CheckSplineMoverEntity(float CurrentLength)
{
	if ((CurrentLength - DeletedSplineLengthsDiff) >= Entity.TopRefreshSplineLength && Refreshable) {

		Refreshable = false;

		// 1.次のSplineUnitを特定し生成
		GenerateNextSpawnedSplineUnit();

		// 2. 古いアクターを消去
		DeleteFirstSpawnedSplineUnit();

		// 3. 古いポイントを一掃しスプラインをリフレッシュする
		UpdateSpline();

		// 4. Entityの更新ポイントをリフレッシュ
		RefreshEntityParameters();

		Refreshable = true;
	}
}

/*
** private
*/

void UProceduralSplineDirector::RefreshEntityParameters()
{
	float SplineLength = 0;
	for (int32 i = 0; i < SpawnedSplineUnits.Num(); i++)
	{
		float number = i + 1;

		if (number == Entity.DisplayableSplineUnitBuffer)
		{
			Entity.RearRefreshSplineLength = SplineLength + (SpawnedSplineUnits[i].Length / 2);
		}
		else if (number == (Entity.DisplayableSplineUnitBuffer + 1 + 1))
		{
			Entity.TopRefreshSplineLength = SplineLength + (SpawnedSplineUnits[i].Length / 2);
		}

		SplineLength += SpawnedSplineUnits[i].Length;

	}
}

void UProceduralSplineDirector::GenerateNextSpawnedSplineUnit()
{
	int32 i = Entity.TopmostNextSpawnableCounter;
	int32 counter = i % SplineUnits.Num();
	FSplineUnit SplineUnit = SplineUnits[counter];
	FSpawnedSplineUnit SpawnedSplineUnit = FSpawnedSplineUnit::GenerateSpawnedSplineUnit(SplineUnit);

	float BeforeTotal = Spline->GetSplineLength();
	ProceduralSplinePointBuilder->AssignPointsToSpline(Spline, SpawnedSplineUnit, SpawnedSplineUnits.Last().NextSpawnPoint);
	ProceduralSplineActorsBuilder->SpawnActors(Owner, Spline, SpawnedSplineUnit);
	SpawnedSplineUnit.DeriveNextSpawnPoint(SpawnedSplineUnits.Top());
	SpawnedSplineUnit.Length = Spline->GetSplineLength() - BeforeTotal;

	SpawnedSplineUnits.Push(SpawnedSplineUnit);

	// TODO 分離
    Entity.TopmostNextSpawnableCounter = i + 1;
}

void UProceduralSplineDirector::DeleteFirstSpawnedSplineUnit()
{
	// TODO 不要なStructをメモリからどう消すか？調査とdebugで監視
	FSpawnedSplineUnit *FirstSpawnedSplineUnit = &SpawnedSplineUnits[0];

	// ここは分離
	DeletedSplineLengthsDiff += FirstSpawnedSplineUnit->Length;

	FirstSpawnedSplineUnit->Destroy();
	SpawnedSplineUnits.RemoveAt(0);
}

void UProceduralSplineDirector::UpdateSpline()
{
	Spline->ClearSplinePoints();
	for (FSpawnedSplineUnit SpawnedSplineUnit: SpawnedSplineUnits)
	{
		for (FAssignedSplineUnitPoint AssignedSplineUnitPoint : SpawnedSplineUnit.AssignedSplineUnitPoints)
		{
			Spline->AddSplinePoint(AssignedSplineUnitPoint.Location, ESplineCoordinateSpace::Type::Local);
		}
	}
}