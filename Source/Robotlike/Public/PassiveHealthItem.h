#pragma once

#include "CoreMinimal.h"
#include "PassiveItemBase.h"
#include "PassiveHealthItem.generated.h"

/**
 * ��ȣ�ۿ� �� �ִ�ü���� +10 �� �ִ� �нú� ������ ������(�ӽ�)��
 */
UCLASS(DisplayName = "����(�ӽ�)")
class ROBOTLIKE_API APassiveHealthItem : public APassiveItemBase
{
    GENERATED_BODY()

public:
    APassiveHealthItem();

    /** ��ȣ�ۿ� �� �ִ�ü�� +10 ȿ�� ���� */
    virtual void OnInteract_Implementation(APawn* InstigatorPawn) override;
};
