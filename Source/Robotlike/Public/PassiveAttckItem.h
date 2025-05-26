#pragma once

#include "CoreMinimal.h"
#include "PassiveItemBase.h"
#include "PassiveAttckItem.generated.h"

/**
 * ��ȣ�ۿ� �� playerAttc �� +0.1 �� �ִ� �нú� ������
 */
UCLASS(DisplayName = "���ݷ� ����(1.1��)")
class ROBOTLIKE_API APassiveAttckItem : public APassiveItemBase
{
    GENERATED_BODY()

public:
    APassiveAttckItem();

    /** ��ȣ�ۿ� �� GameManager ���� ���ݷ� ����� +0.1 �� �޶�� ��û */
    virtual void OnInteract_Implementation(APawn* InstigatorPawn) override;
};
