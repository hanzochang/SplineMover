
#include "SplineMoverPrivatePCH.h"
#include "AssignedSplineUnitPoint.h"

FAssignedSplineUnitPoint FAssignedSplineUnitPoint::GenerateAssignedSplineUnitPoint(USplineComponent *Spline, int32 PointsIndex)
{
	FAssignedSplineUnitPoint AssignedSplineUnitPoint;
	AssignedSplineUnitPoint.Location = Spline->GetLocationAtSplinePoint(PointsIndex, ESplineCoordinateSpace::Type::Local);
	AssignedSplineUnitPoint.Direction = Spline->GetDirectionAtSplinePoint(PointsIndex, ESplineCoordinateSpace::Type::Local);
	AssignedSplineUnitPoint.Rotation = Spline->GetRotationAtSplinePoint(PointsIndex, ESplineCoordinateSpace::Type::Local);
	AssignedSplineUnitPoint.Index = PointsIndex;

	return AssignedSplineUnitPoint;
}