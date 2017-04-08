#pragma once

#include "SplineMoverEntity.generated.h"

USTRUCT(BlueprintType)
struct SPLINEMOVER_API FSplineMoverEntity
{
	GENERATED_USTRUCT_BODY()

public:
	FSplineMoverEntity(int32 UnitLimit = 1);
	FString ToDebugString();

    // ���݂�SplineUnit����̓����\���\�ȃo�b�t�@�����K��
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 DisplayableSplineUnitBuffer;

	// ���̐�[��Spawn�\��counter�ԍ�
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 TopmostNextSpawnableCounter;

	// ���̌�[��Spawn�\��counter�ԍ�
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 RearmostNextSpawnableCounter;

    // ����PointBuilder/AssetsBuilder�̋N���|�C���g
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	float TopRefreshSplineLength;

    // �߂�ꍇ��PointBuilder/AssetsBuilder�̋N���|�C���g
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	float RearRefreshSplineLength;

public:
	// �����\���\��SplineUnit�̐����v�l
	int32 DisplayableSplineUnitSum();

};